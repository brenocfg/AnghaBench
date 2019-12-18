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
struct io_uring_sqe {int dummy; } ;
struct io_uring {int dummy; } ;
struct io_data {int /*<<< orphan*/  offset; int /*<<< orphan*/  iov; scalar_t__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct io_uring_sqe*) ; 
 int /*<<< orphan*/  infd ; 
 struct io_uring_sqe* io_uring_get_sqe (struct io_uring*) ; 
 int /*<<< orphan*/  io_uring_prep_readv (struct io_uring_sqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_uring_prep_writev (struct io_uring_sqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_uring_sqe_set_data (struct io_uring_sqe*,struct io_data*) ; 
 int /*<<< orphan*/  outfd ; 

__attribute__((used)) static void queue_prepped(struct io_uring *ring, struct io_data *data)
{
	struct io_uring_sqe *sqe;

	sqe = io_uring_get_sqe(ring);
	assert(sqe);

	if (data->read)
		io_uring_prep_readv(sqe, infd, &data->iov, 1, data->offset);
	else
		io_uring_prep_writev(sqe, outfd, &data->iov, 1, data->offset);

	io_uring_sqe_set_data(sqe, data);
}