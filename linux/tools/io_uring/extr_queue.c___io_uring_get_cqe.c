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
struct io_uring_cqe {int dummy; } ;
struct io_uring_cq {unsigned int* kring_mask; unsigned int* khead; unsigned int* ktail; struct io_uring_cqe* cqes; } ;
struct io_uring {int /*<<< orphan*/  ring_fd; struct io_uring_cq cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORING_ENTER_GETEVENTS ; 
 int errno ; 
 int io_uring_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_barrier () ; 

__attribute__((used)) static int __io_uring_get_cqe(struct io_uring *ring,
			      struct io_uring_cqe **cqe_ptr, int wait)
{
	struct io_uring_cq *cq = &ring->cq;
	const unsigned mask = *cq->kring_mask;
	unsigned head;
	int ret;

	*cqe_ptr = NULL;
	head = *cq->khead;
	do {
		/*
		 * It's necessary to use a read_barrier() before reading
		 * the CQ tail, since the kernel updates it locklessly. The
		 * kernel has the matching store barrier for the update. The
		 * kernel also ensures that previous stores to CQEs are ordered
		 * with the tail update.
		 */
		read_barrier();
		if (head != *cq->ktail) {
			*cqe_ptr = &cq->cqes[head & mask];
			break;
		}
		if (!wait)
			break;
		ret = io_uring_enter(ring->ring_fd, 0, 1,
					IORING_ENTER_GETEVENTS, NULL);
		if (ret < 0)
			return -errno;
	} while (1);

	return 0;
}