#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct kstat {int dummy; } ;
struct inode {int i_mode; } ;
struct TYPE_17__ {int mode; } ;
struct fuse_getattr_in {TYPE_7__ attr; int /*<<< orphan*/  fh; int /*<<< orphan*/  getattr_flags; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int dummy; } ;
struct fuse_attr_out {TYPE_7__ attr; int /*<<< orphan*/  fh; int /*<<< orphan*/  getattr_flags; } ;
struct file {struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  outarg ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_15__ {int numargs; TYPE_4__* args; } ;
struct TYPE_11__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_13__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct TYPE_16__ {TYPE_5__ out; TYPE_3__ in; } ;
struct TYPE_14__ {int size; struct fuse_getattr_in* value; } ;
struct TYPE_12__ {int size; struct fuse_getattr_in* value; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_6__) ; 
 int /*<<< orphan*/  FUSE_GETATTR ; 
 int /*<<< orphan*/  FUSE_GETATTR_FH ; 
 int S_IFMT ; 
 scalar_t__ S_ISREG (int) ; 
 TYPE_6__ args ; 
 int /*<<< orphan*/  attr_timeout (struct fuse_getattr_in*) ; 
 int /*<<< orphan*/  fuse_change_attributes (struct inode*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_fillattr (struct inode*,TYPE_7__*,struct kstat*) ; 
 int /*<<< orphan*/  fuse_get_attr_version (struct fuse_conn*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_6__*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_getattr_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fuse_do_getattr(struct inode *inode, struct kstat *stat,
			   struct file *file)
{
	int err;
	struct fuse_getattr_in inarg;
	struct fuse_attr_out outarg;
	struct fuse_conn *fc = get_fuse_conn(inode);
	FUSE_ARGS(args);
	u64 attr_version;

	attr_version = fuse_get_attr_version(fc);

	memset(&inarg, 0, sizeof(inarg));
	memset(&outarg, 0, sizeof(outarg));
	/* Directories have separate file-handle space */
	if (file && S_ISREG(inode->i_mode)) {
		struct fuse_file *ff = file->private_data;

		inarg.getattr_flags |= FUSE_GETATTR_FH;
		inarg.fh = ff->fh;
	}
	args.in.h.opcode = FUSE_GETATTR;
	args.in.h.nodeid = get_node_id(inode);
	args.in.numargs = 1;
	args.in.args[0].size = sizeof(inarg);
	args.in.args[0].value = &inarg;
	args.out.numargs = 1;
	args.out.args[0].size = sizeof(outarg);
	args.out.args[0].value = &outarg;
	err = fuse_simple_request(fc, &args);
	if (!err) {
		if ((inode->i_mode ^ outarg.attr.mode) & S_IFMT) {
			make_bad_inode(inode);
			err = -EIO;
		} else {
			fuse_change_attributes(inode, &outarg.attr,
					       attr_timeout(&outarg),
					       attr_version);
			if (stat)
				fuse_fillattr(inode, &outarg.attr, stat);
		}
	}
	return err;
}