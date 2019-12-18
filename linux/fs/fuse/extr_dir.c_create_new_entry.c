#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fuse_forget_link {int dummy; } ;
struct TYPE_4__ {int mode; } ;
struct fuse_entry_out {int /*<<< orphan*/  nodeid; TYPE_2__ attr; int /*<<< orphan*/  generation; } ;
struct fuse_conn {int dummy; } ;
struct fuse_args {int out_numargs; TYPE_1__* out_args; int /*<<< orphan*/  nodeid; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  outarg ;
struct TYPE_3__ {int size; struct fuse_entry_out* value; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFMT ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  entry_attr_timeout (struct fuse_entry_out*) ; 
 struct fuse_forget_link* fuse_alloc_forget () ; 
 int /*<<< orphan*/  fuse_change_entry_timeout (struct dentry*,struct fuse_entry_out*) ; 
 int /*<<< orphan*/  fuse_dir_changed (struct inode*) ; 
 struct inode* fuse_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_queue_forget (struct fuse_conn*,struct fuse_forget_link*,int /*<<< orphan*/ ,int) ; 
 int fuse_simple_request (struct fuse_conn*,struct fuse_args*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 scalar_t__ invalid_nodeid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fuse_forget_link*) ; 
 int /*<<< orphan*/  memset (struct fuse_entry_out*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int create_new_entry(struct fuse_conn *fc, struct fuse_args *args,
			    struct inode *dir, struct dentry *entry,
			    umode_t mode)
{
	struct fuse_entry_out outarg;
	struct inode *inode;
	struct dentry *d;
	int err;
	struct fuse_forget_link *forget;

	forget = fuse_alloc_forget();
	if (!forget)
		return -ENOMEM;

	memset(&outarg, 0, sizeof(outarg));
	args->nodeid = get_node_id(dir);
	args->out_numargs = 1;
	args->out_args[0].size = sizeof(outarg);
	args->out_args[0].value = &outarg;
	err = fuse_simple_request(fc, args);
	if (err)
		goto out_put_forget_req;

	err = -EIO;
	if (invalid_nodeid(outarg.nodeid))
		goto out_put_forget_req;

	if ((outarg.attr.mode ^ mode) & S_IFMT)
		goto out_put_forget_req;

	inode = fuse_iget(dir->i_sb, outarg.nodeid, outarg.generation,
			  &outarg.attr, entry_attr_timeout(&outarg), 0);
	if (!inode) {
		fuse_queue_forget(fc, forget, outarg.nodeid, 1);
		return -ENOMEM;
	}
	kfree(forget);

	d_drop(entry);
	d = d_splice_alias(inode, entry);
	if (IS_ERR(d))
		return PTR_ERR(d);

	if (d) {
		fuse_change_entry_timeout(d, &outarg);
		dput(d);
	} else {
		fuse_change_entry_timeout(entry, &outarg);
	}
	fuse_dir_changed(dir);
	return 0;

 out_put_forget_req:
	kfree(forget);
	return err;
}