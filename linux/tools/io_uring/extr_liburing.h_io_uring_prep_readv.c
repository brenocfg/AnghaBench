#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iovec {int dummy; } ;
struct io_uring_sqe {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  IORING_OP_READV ; 
 int /*<<< orphan*/  io_uring_prep_rw (int /*<<< orphan*/ ,struct io_uring_sqe*,int,struct iovec const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void io_uring_prep_readv(struct io_uring_sqe *sqe, int fd,
				       const struct iovec *iovecs,
				       unsigned nr_vecs, off_t offset)
{
	io_uring_prep_rw(IORING_OP_READV, sqe, fd, iovecs, nr_vecs, offset);
}