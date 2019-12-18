#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct io_uring_sqe {int dummy; } ;
struct io_uring_sq {size_t ring_sz; void* khead; void* sqes; void* array; void* kdropped; void* kflags; void* kring_entries; void* kring_mask; void* ktail; } ;
struct TYPE_4__ {size_t cqes; int head; int tail; int ring_mask; int ring_entries; int overflow; } ;
struct TYPE_3__ {size_t array; int head; int tail; int ring_mask; int ring_entries; int flags; int dropped; } ;
struct io_uring_params {int sq_entries; int cq_entries; TYPE_2__ cq_off; TYPE_1__ sq_off; } ;
struct io_uring_cqe {int dummy; } ;
struct io_uring_cq {size_t ring_sz; void* cqes; void* koverflow; void* kring_entries; void* kring_mask; void* ktail; void* khead; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORING_OFF_CQ_RING ; 
 int /*<<< orphan*/  IORING_OFF_SQES ; 
 int /*<<< orphan*/  IORING_OFF_SQ_RING ; 
 void* MAP_FAILED ; 
 int MAP_POPULATE ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int errno ; 
 void* mmap (int /*<<< orphan*/ ,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 

__attribute__((used)) static int io_uring_mmap(int fd, struct io_uring_params *p,
			 struct io_uring_sq *sq, struct io_uring_cq *cq)
{
	size_t size;
	void *ptr;
	int ret;

	sq->ring_sz = p->sq_off.array + p->sq_entries * sizeof(unsigned);
	ptr = mmap(0, sq->ring_sz, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_SQ_RING);
	if (ptr == MAP_FAILED)
		return -errno;
	sq->khead = ptr + p->sq_off.head;
	sq->ktail = ptr + p->sq_off.tail;
	sq->kring_mask = ptr + p->sq_off.ring_mask;
	sq->kring_entries = ptr + p->sq_off.ring_entries;
	sq->kflags = ptr + p->sq_off.flags;
	sq->kdropped = ptr + p->sq_off.dropped;
	sq->array = ptr + p->sq_off.array;

	size = p->sq_entries * sizeof(struct io_uring_sqe);
	sq->sqes = mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_POPULATE, fd,
				IORING_OFF_SQES);
	if (sq->sqes == MAP_FAILED) {
		ret = -errno;
err:
		munmap(sq->khead, sq->ring_sz);
		return ret;
	}

	cq->ring_sz = p->cq_off.cqes + p->cq_entries * sizeof(struct io_uring_cqe);
	ptr = mmap(0, cq->ring_sz, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_CQ_RING);
	if (ptr == MAP_FAILED) {
		ret = -errno;
		munmap(sq->sqes, p->sq_entries * sizeof(struct io_uring_sqe));
		goto err;
	}
	cq->khead = ptr + p->cq_off.head;
	cq->ktail = ptr + p->cq_off.tail;
	cq->kring_mask = ptr + p->cq_off.ring_mask;
	cq->kring_entries = ptr + p->cq_off.ring_entries;
	cq->koverflow = ptr + p->cq_off.overflow;
	cq->cqes = ptr + p->cq_off.cqes;
	return 0;
}