#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_3__ in; } ;
struct fuse_args {int in_numargs; int out_numargs; TYPE_5__* out_args; TYPE_4__* in_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_7__ {struct fuse_args args; } ;
struct fuse_io_args {TYPE_6__ write; TYPE_1__ ap; } ;
struct fuse_file {TYPE_2__* fc; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * value; } ;
struct TYPE_10__ {int size; TYPE_3__* value; } ;
struct TYPE_8__ {int minor; } ;

/* Variables and functions */
 int FUSE_COMPAT_WRITE_IN_SIZE ; 
 int /*<<< orphan*/  FUSE_WRITE ; 

__attribute__((used)) static void fuse_write_args_fill(struct fuse_io_args *ia, struct fuse_file *ff,
				 loff_t pos, size_t count)
{
	struct fuse_args *args = &ia->ap.args;

	ia->write.in.fh = ff->fh;
	ia->write.in.offset = pos;
	ia->write.in.size = count;
	args->opcode = FUSE_WRITE;
	args->nodeid = ff->nodeid;
	args->in_numargs = 2;
	if (ff->fc->minor < 9)
		args->in_args[0].size = FUSE_COMPAT_WRITE_IN_SIZE;
	else
		args->in_args[0].size = sizeof(ia->write.in);
	args->in_args[0].value = &ia->write.in;
	args->in_args[1].size = count;
	args->out_numargs = 1;
	args->out_args[0].size = sizeof(ia->write.out);
	args->out_args[0].value = &ia->write.out;
}