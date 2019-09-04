#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {scalar_t__ i_nlink; } ;
struct fuse_inode {scalar_t__ attr_version; } ;
struct fuse_conn {int /*<<< orphan*/  lock; scalar_t__ attr_version; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct dentry {TYPE_4__ d_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct TYPE_12__ {TYPE_3__ in; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; scalar_t__ size; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_UNLINK ; 
 TYPE_5__ args ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry (struct dentry*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry_cache (struct dentry*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_5__*) ; 
 int /*<<< orphan*/  fuse_update_ctime (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_unlink(struct inode *dir, struct dentry *entry)
{
	int err;
	struct fuse_conn *fc = get_fuse_conn(dir);
	FUSE_ARGS(args);

	args.in.h.opcode = FUSE_UNLINK;
	args.in.h.nodeid = get_node_id(dir);
	args.in.numargs = 1;
	args.in.args[0].size = entry->d_name.len + 1;
	args.in.args[0].value = entry->d_name.name;
	err = fuse_simple_request(fc, &args);
	if (!err) {
		struct inode *inode = d_inode(entry);
		struct fuse_inode *fi = get_fuse_inode(inode);

		spin_lock(&fc->lock);
		fi->attr_version = ++fc->attr_version;
		/*
		 * If i_nlink == 0 then unlink doesn't make sense, yet this can
		 * happen if userspace filesystem is careless.  It would be
		 * difficult to enforce correct nlink usage so just ignore this
		 * condition here
		 */
		if (inode->i_nlink > 0)
			drop_nlink(inode);
		spin_unlock(&fc->lock);
		fuse_invalidate_attr(inode);
		fuse_invalidate_attr(dir);
		fuse_invalidate_entry_cache(entry);
		fuse_update_ctime(inode);
	} else if (err == -EINTR)
		fuse_invalidate_entry(entry);
	return err;
}