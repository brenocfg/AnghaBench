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
struct inode {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct dentry {TYPE_4__ d_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct TYPE_12__ {TYPE_3__ in; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; scalar_t__ size; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_RMDIR ; 
 TYPE_5__ args ; 
 int /*<<< orphan*/  clear_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry (struct dentry*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry_cache (struct dentry*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_5__*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 

__attribute__((used)) static int fuse_rmdir(struct inode *dir, struct dentry *entry)
{
	int err;
	struct fuse_conn *fc = get_fuse_conn(dir);
	FUSE_ARGS(args);

	args.in.h.opcode = FUSE_RMDIR;
	args.in.h.nodeid = get_node_id(dir);
	args.in.numargs = 1;
	args.in.args[0].size = entry->d_name.len + 1;
	args.in.args[0].value = entry->d_name.name;
	err = fuse_simple_request(fc, &args);
	if (!err) {
		clear_nlink(d_inode(entry));
		fuse_invalidate_attr(dir);
		fuse_invalidate_entry_cache(entry);
	} else if (err == -EINTR)
		fuse_invalidate_entry(entry);
	return err;
}