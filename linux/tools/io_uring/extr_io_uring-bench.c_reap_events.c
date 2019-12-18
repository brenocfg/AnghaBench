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
struct io_cq_ring {unsigned int* head; unsigned int* tail; struct io_uring_cqe* cqes; } ;
struct submitter {unsigned int inflight; struct io_cq_ring cq_ring; } ;
struct io_uring_cqe {int res; scalar_t__ user_data; } ;
struct file {int /*<<< orphan*/  pending_ios; } ;

/* Variables and functions */
 int BS ; 
 int EOPNOTSUPP ; 
 unsigned int cq_ring_mask ; 
 int /*<<< orphan*/  do_nop ; 
 scalar_t__ polled ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_barrier () ; 
 int /*<<< orphan*/  write_barrier () ; 

__attribute__((used)) static int reap_events(struct submitter *s)
{
	struct io_cq_ring *ring = &s->cq_ring;
	struct io_uring_cqe *cqe;
	unsigned head, reaped = 0;

	head = *ring->head;
	do {
		struct file *f;

		read_barrier();
		if (head == *ring->tail)
			break;
		cqe = &ring->cqes[head & cq_ring_mask];
		if (!do_nop) {
			f = (struct file *) (uintptr_t) cqe->user_data;
			f->pending_ios--;
			if (cqe->res != BS) {
				printf("io: unexpected ret=%d\n", cqe->res);
				if (polled && cqe->res == -EOPNOTSUPP)
					printf("Your filesystem doesn't support poll\n");
				return -1;
			}
		}
		reaped++;
		head++;
	} while (1);

	s->inflight -= reaped;
	*ring->head = head;
	write_barrier();
	return reaped;
}