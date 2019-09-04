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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct fuse_link_in {int /*<<< orphan*/  oldnodeid; } ;
struct fuse_inode {scalar_t__ attr_version; } ;
struct fuse_conn {int /*<<< orphan*/  lock; scalar_t__ attr_version; } ;
struct TYPE_11__ {int len; struct fuse_link_in* name; } ;
struct dentry {TYPE_4__ d_name; } ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct TYPE_12__ {TYPE_3__ in; } ;
struct TYPE_9__ {int size; struct fuse_link_in* value; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_LINK ; 
 TYPE_5__ args ; 
 int create_new_entry (struct fuse_conn*,TYPE_5__*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
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
	args.in.h.opcode = FUSE_LINK;
	args.in.numargs = 2;
	args.in.args[0].size = sizeof(inarg);
	args.in.args[0].value = &inarg;
	args.in.args[1].size = newent->d_name.len + 1;
	args.in.args[1].value = newent->d_name.name;
	err = create_new_entry(fc, &args, newdir, newent, inode->i_mode);
	/* Contrary to "normal" filesystems it can happen that link
	   makes two "logical" inodes point to the same "physical"
	   inode.  We invalidate the attributes of the old one, so it
	   will reflect changes in the backing inode (link count,
	   etc.)
	*/
	if (!err) {
		struct fuse_inode *fi = get_fuse_inode(inode);

		spin_lock(&fc->lock);
		fi->attr_version = ++fc->attr_version;
		inc_nlink(inode);
		spin_unlock(&fc->lock);
		fuse_invalidate_attr(inode);
		fuse_update_ctime(inode);
	} else if (err == -EINTR) {
		fuse_invalidate_attr(inode);
	}
	return err;
}