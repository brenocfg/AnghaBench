#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  index; } ;
struct key {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  wb_lock; int /*<<< orphan*/  vfs_inode; TYPE_1__ fid; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key* afs_file_key (struct file*) ; 
 int afs_fill_page (struct afs_vnode*,struct key*,scalar_t__,unsigned int,struct page*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_write (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int afs_write_end(struct file *file, struct address_space *mapping,
		  loff_t pos, unsigned len, unsigned copied,
		  struct page *page, void *fsdata)
{
	struct afs_vnode *vnode = AFS_FS_I(file_inode(file));
	struct key *key = afs_file_key(file);
	loff_t i_size, maybe_i_size;
	int ret;

	_enter("{%llx:%llu},{%lx}",
	       vnode->fid.vid, vnode->fid.vnode, page->index);

	maybe_i_size = pos + copied;

	i_size = i_size_read(&vnode->vfs_inode);
	if (maybe_i_size > i_size) {
		spin_lock(&vnode->wb_lock);
		i_size = i_size_read(&vnode->vfs_inode);
		if (maybe_i_size > i_size)
			i_size_write(&vnode->vfs_inode, maybe_i_size);
		spin_unlock(&vnode->wb_lock);
	}

	if (!PageUptodate(page)) {
		if (copied < len) {
			/* Try and load any missing data from the server.  The
			 * unmarshalling routine will take care of clearing any
			 * bits that are beyond the EOF.
			 */
			ret = afs_fill_page(vnode, key, pos + copied,
					    len - copied, page);
			if (ret < 0)
				goto out;
		}
		SetPageUptodate(page);
	}

	set_page_dirty(page);
	if (PageDirty(page))
		_debug("dirtied");
	ret = copied;

out:
	unlock_page(page);
	put_page(page);
	return ret;
}