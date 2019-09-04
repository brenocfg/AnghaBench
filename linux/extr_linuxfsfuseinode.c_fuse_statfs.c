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
struct super_block {int dummy; } ;
struct kstatfs {int /*<<< orphan*/  f_type; } ;
struct fuse_statfs_out {int /*<<< orphan*/  st; } ;
struct fuse_conn {int dummy; } ;
struct dentry {struct super_block* d_sb; } ;
typedef  int /*<<< orphan*/  outarg ;
struct TYPE_11__ {int numargs; TYPE_3__* args; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_9__ {TYPE_1__ h; scalar_t__ numargs; } ;
struct TYPE_12__ {TYPE_4__ out; TYPE_2__ in; } ;
struct TYPE_10__ {int size; struct fuse_statfs_out* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_STATFS ; 
 int /*<<< orphan*/  FUSE_SUPER_MAGIC ; 
 TYPE_5__ args ; 
 int /*<<< orphan*/  convert_fuse_statfs (struct kstatfs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fuse_allow_current_process (struct fuse_conn*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_5__*) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 
 int /*<<< orphan*/  get_node_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fuse_statfs_out*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fuse_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct fuse_conn *fc = get_fuse_conn_super(sb);
	FUSE_ARGS(args);
	struct fuse_statfs_out outarg;
	int err;

	if (!fuse_allow_current_process(fc)) {
		buf->f_type = FUSE_SUPER_MAGIC;
		return 0;
	}

	memset(&outarg, 0, sizeof(outarg));
	args.in.numargs = 0;
	args.in.h.opcode = FUSE_STATFS;
	args.in.h.nodeid = get_node_id(d_inode(dentry));
	args.out.numargs = 1;
	args.out.args[0].size = sizeof(outarg);
	args.out.args[0].value = &outarg;
	err = fuse_simple_request(fc, &args);
	if (!err)
		convert_fuse_statfs(buf, &outarg.st);
	return err;
}