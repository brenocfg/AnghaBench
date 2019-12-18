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
struct io_uring_cq {int /*<<< orphan*/ * khead; } ;
struct io_uring {struct io_uring_cq cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_barrier () ; 

__attribute__((used)) static inline void io_uring_cqe_seen(struct io_uring *ring,
				     struct io_uring_cqe *cqe)
{
	if (cqe) {
		struct io_uring_cq *cq = &ring->cq;

		(*cq->khead)++;
		/*
		 * Ensure that the kernel sees our new head, the kernel has
		 * the matching read barrier.
		 */
		write_barrier();
	}
}