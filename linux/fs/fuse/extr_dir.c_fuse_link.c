#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mode; } ;
struct fuse_link_in {int /*<<< orphan*/  oldnodeid; } ;
struct fuse_inode {int /*<<< orphan*/  lock; int /*<<< orphan*/  attr_version; } ;
struct fuse_conn {int /*<<< orphan*/  attr_version; } ;
struct TYPE_7__ {int len; struct fuse_link_in* name; } ;
struct dentry {TYPE_2__ d_name; } ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_8__ {int in_numargs; TYPE_1__* in_args; int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {int size; struct fuse_link_in* value; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_3__) ; 
 int /*<<< orphan*/  FUSE_LINK ; 
 TYPE_3__ args ; 
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int create_new_entry (struct fuse_conn*,TYPE_3__*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_update_ctime (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_link_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_link(struct dentry *entry, struct inode *newdir,
		     struct dentry *newent)
{
	int err;
	struct fuse_link_in inarg;
	struct inode *inode = d_inode(entry);
	struct fuse_conn *fc = get_fuse_conn(inode);
	FUSE_ARGS(args);

	memset(&inarg, 0, sizeof(inarg));
	inarg.oldnodeid = get_node_id(inode);
	args.opcode = FUSE_LINK;
	args.in_numargs = 2;
	args.in_args[0].size = sizeof(inarg);
	args.in_args[0].value = &inarg;
	args.in_args[1].size = newent->d_name.len + 1;
	args.in_args[1].value = newent->d_name.name;
	err = create_new_entry(fc, &args, newdir, newent, inode->i_mode);
	/* Contrary to "normal" filesystems it can happen that link
	   makes two "logical" inodes point to the same "physical"
	   inode.  We invalidate the attributes of the old one, so it
	   will reflect changes in the backing inode (link count,
	   etc.)
	*/
	if (!err) {
		struct fuse_inode *fi = get_fuse_inode(inode);

		spin_lock(&fi->lock);
		fi->attr_version = atomic64_inc_return(&fc->attr_version);
		inc_nlink(inode);
		spin_unlock(&fi->lock);
		fuse_invalidate_attr(inode);
		fuse_update_ctime(inode);
	} else if (err == -EINTR) {
		fuse_invalidate_attr(inode);
	}
	return err;
}