#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct submitter {int nr_files; size_t cur_file; TYPE_1__* iovecs; int /*<<< orphan*/  rand; struct file* files; struct io_uring_sqe* sqes; } ;
struct io_uring_sqe {unsigned long addr; long len; unsigned int buf_index; unsigned long off; unsigned long user_data; scalar_t__ ioprio; int /*<<< orphan*/  opcode; int /*<<< orphan*/  fd; scalar_t__ flags; } ;
struct file {scalar_t__ pending_ios; int max_blocks; int /*<<< orphan*/  real_fd; int /*<<< orphan*/  fixed_fd; } ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 long BS ; 
 int /*<<< orphan*/  IORING_OP_NOP ; 
 int /*<<< orphan*/  IORING_OP_READV ; 
 int /*<<< orphan*/  IORING_OP_READ_FIXED ; 
 scalar_t__ IOSQE_FIXED_FILE ; 
 scalar_t__ do_nop ; 
 scalar_t__ file_depth (struct submitter*) ; 
 scalar_t__ fixedbufs ; 
 int /*<<< orphan*/  lrand48_r (int /*<<< orphan*/ *,long*) ; 
 scalar_t__ register_files ; 

__attribute__((used)) static void init_io(struct submitter *s, unsigned index)
{
	struct io_uring_sqe *sqe = &s->sqes[index];
	unsigned long offset;
	struct file *f;
	long r;

	if (do_nop) {
		sqe->opcode = IORING_OP_NOP;
		return;
	}

	if (s->nr_files == 1) {
		f = &s->files[0];
	} else {
		f = &s->files[s->cur_file];
		if (f->pending_ios >= file_depth(s)) {
			s->cur_file++;
			if (s->cur_file == s->nr_files)
				s->cur_file = 0;
			f = &s->files[s->cur_file];
		}
	}
	f->pending_ios++;

	lrand48_r(&s->rand, &r);
	offset = (r % (f->max_blocks - 1)) * BS;

	if (register_files) {
		sqe->flags = IOSQE_FIXED_FILE;
		sqe->fd = f->fixed_fd;
	} else {
		sqe->flags = 0;
		sqe->fd = f->real_fd;
	}
	if (fixedbufs) {
		sqe->opcode = IORING_OP_READ_FIXED;
		sqe->addr = (unsigned long) s->iovecs[index].iov_base;
		sqe->len = BS;
		sqe->buf_index = index;
	} else {
		sqe->opcode = IORING_OP_READV;
		sqe->addr = (unsigned long) &s->iovecs[index];
		sqe->len = 1;
		sqe->buf_index = 0;
	}
	sqe->ioprio = 0;
	sqe->off = offset;
	sqe->user_data = (unsigned long) f;
}