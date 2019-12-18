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
struct inode {TYPE_4__* i_sb; } ;
struct fuse_lseek_out {int /*<<< orphan*/  offset; } ;
struct fuse_lseek_in {int offset; int whence; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_lseek; } ;
struct file {struct fuse_file* private_data; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  outarg ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_12__ {int in_numargs; int out_numargs; TYPE_3__* out_args; TYPE_2__* in_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_maxbytes; } ;
struct TYPE_10__ {int size; struct fuse_lseek_out* value; } ;
struct TYPE_9__ {int size; struct fuse_lseek_in* value; } ;
struct TYPE_8__ {struct inode* host; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_LSEEK ; 
 TYPE_5__ args ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_5__*) ; 
 int fuse_update_attributes (struct inode*,struct file*) ; 
 int generic_file_llseek (struct file*,int,int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int vfs_setpos (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t fuse_lseek(struct file *file, loff_t offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;
	FUSE_ARGS(args);
	struct fuse_lseek_in inarg = {
		.fh = ff->fh,
		.offset = offset,
		.whence = whence
	};
	struct fuse_lseek_out outarg;
	int err;

	if (fc->no_lseek)
		goto fallback;

	args.opcode = FUSE_LSEEK;
	args.nodeid = ff->nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = sizeof(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = sizeof(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fc, &args);
	if (err) {
		if (err == -ENOSYS) {
			fc->no_lseek = 1;
			goto fallback;
		}
		return err;
	}

	return vfs_setpos(file, outarg.offset, inode->i_sb->s_maxbytes);

fallback:
	err = fuse_update_attributes(inode, file);
	if (!err)
		return generic_file_llseek(file, offset, whence);
	else
		return err;
}