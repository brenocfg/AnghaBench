#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_7__ {unsigned int len; char* name; } ;
struct dentry {int /*<<< orphan*/  d_sb; TYPE_1__ d_name; } ;
struct afs_vnode {int /*<<< orphan*/  flags; } ;
struct afs_super_info {TYPE_3__* volume; TYPE_2__* cell; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  afs_root_cell ;
struct TYPE_10__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AFSVL_RWVOL ; 
 struct afs_vnode* AFS_FS_I (TYPE_4__*) ; 
 struct afs_super_info* AFS_FS_S (int /*<<< orphan*/ ) ; 
 unsigned int AFS_MAXCELLNAME ; 
 int /*<<< orphan*/  AFS_VNODE_PSEUDODIR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct vfsmount* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  _debug (char*,char*,...) ; 
 int /*<<< orphan*/  _enter (char*,struct dentry*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  afs_fs_type ; 
 TYPE_4__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int i_size_read (TYPE_4__*) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vfsmount* vfs_submount (struct dentry*,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static struct vfsmount *afs_mntpt_do_automount(struct dentry *mntpt)
{
	struct afs_super_info *as;
	struct vfsmount *mnt;
	struct afs_vnode *vnode;
	struct page *page;
	char *devname, *options;
	bool rwpath = false;
	int ret;

	_enter("{%pd}", mntpt);

	BUG_ON(!d_inode(mntpt));

	ret = -ENOMEM;
	devname = (char *) get_zeroed_page(GFP_KERNEL);
	if (!devname)
		goto error_no_devname;

	options = (char *) get_zeroed_page(GFP_KERNEL);
	if (!options)
		goto error_no_options;

	vnode = AFS_FS_I(d_inode(mntpt));
	if (test_bit(AFS_VNODE_PSEUDODIR, &vnode->flags)) {
		/* if the directory is a pseudo directory, use the d_name */
		static const char afs_root_cell[] = ":root.cell.";
		unsigned size = mntpt->d_name.len;

		ret = -ENOENT;
		if (size < 2 || size > AFS_MAXCELLNAME)
			goto error_no_page;

		if (mntpt->d_name.name[0] == '.') {
			devname[0] = '%';
			memcpy(devname + 1, mntpt->d_name.name + 1, size - 1);
			memcpy(devname + size, afs_root_cell,
			       sizeof(afs_root_cell));
			rwpath = true;
		} else {
			devname[0] = '#';
			memcpy(devname + 1, mntpt->d_name.name, size);
			memcpy(devname + size + 1, afs_root_cell,
			       sizeof(afs_root_cell));
		}
	} else {
		/* read the contents of the AFS special symlink */
		loff_t size = i_size_read(d_inode(mntpt));
		char *buf;

		ret = -EINVAL;
		if (size > PAGE_SIZE - 1)
			goto error_no_page;

		page = read_mapping_page(d_inode(mntpt)->i_mapping, 0, NULL);
		if (IS_ERR(page)) {
			ret = PTR_ERR(page);
			goto error_no_page;
		}

		ret = -EIO;
		if (PageError(page))
			goto error;

		buf = kmap_atomic(page);
		memcpy(devname, buf, size);
		kunmap_atomic(buf);
		put_page(page);
		page = NULL;
	}

	/* work out what options we want */
	as = AFS_FS_S(mntpt->d_sb);
	if (as->cell) {
		memcpy(options, "cell=", 5);
		strcpy(options + 5, as->cell->name);
		if ((as->volume && as->volume->type == AFSVL_RWVOL) || rwpath)
			strcat(options, ",rwpath");
	}

	/* try and do the mount */
	_debug("--- attempting mount %s -o %s ---", devname, options);
	mnt = vfs_submount(mntpt, &afs_fs_type, devname, options);
	_debug("--- mount result %p ---", mnt);

	free_page((unsigned long) devname);
	free_page((unsigned long) options);
	_leave(" = %p", mnt);
	return mnt;

error:
	put_page(page);
error_no_page:
	free_page((unsigned long) options);
error_no_options:
	free_page((unsigned long) devname);
error_no_devname:
	_leave(" = %d", ret);
	return ERR_PTR(ret);
}