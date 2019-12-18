#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  args; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  read_flags; } ;
struct TYPE_7__ {TYPE_1__ in; } ;
struct fuse_io_args {TYPE_3__ ap; TYPE_5__* io; TYPE_2__ read; } ;
struct fuse_file {struct fuse_conn* fc; } ;
struct fuse_conn {int dummy; } ;
struct file {struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/ * fl_owner_t ;
struct TYPE_10__ {scalar_t__ async; TYPE_4__* iocb; } ;
struct TYPE_9__ {struct file* ki_filp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_READ ; 
 int /*<<< orphan*/  FUSE_READ_LOCKOWNER ; 
 int /*<<< orphan*/  fuse_async_req_send (struct fuse_conn*,struct fuse_io_args*,size_t) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_read_args_fill (struct fuse_io_args*,struct file*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_simple_request (struct fuse_conn*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fuse_send_read(struct fuse_io_args *ia, loff_t pos, size_t count,
			      fl_owner_t owner)
{
	struct file *file = ia->io->iocb->ki_filp;
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = ff->fc;

	fuse_read_args_fill(ia, file, pos, count, FUSE_READ);
	if (owner != NULL) {
		ia->read.in.read_flags |= FUSE_READ_LOCKOWNER;
		ia->read.in.lock_owner = fuse_lock_owner_id(fc, owner);
	}

	if (ia->io->async)
		return fuse_async_req_send(fc, ia, count);

	return fuse_simple_request(fc, &ia->ap.args);
}