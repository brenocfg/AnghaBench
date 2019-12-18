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
struct io_cq_ring {int /*<<< orphan*/ * ring_mask; void* cqes; void* ring_entries; void* tail; void* head; } ;
struct io_sq_ring {int /*<<< orphan*/ * ring_mask; void* array; void* flags; void* ring_entries; void* tail; void* head; } ;
struct submitter {int ring_fd; void* sqes; struct io_cq_ring cq_ring; struct io_sq_ring sq_ring; } ;
struct io_uring_sqe {int dummy; } ;
struct TYPE_4__ {int cqes; int head; int tail; int ring_mask; int ring_entries; } ;
struct TYPE_3__ {int array; int head; int tail; int ring_mask; int ring_entries; int flags; } ;
struct io_uring_params {int sq_thread_cpu; int sq_entries; int cq_entries; TYPE_2__ cq_off; TYPE_1__ sq_off; int /*<<< orphan*/  flags; } ;
struct io_uring_cqe {int dummy; } ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEPTH ; 
 int /*<<< orphan*/  IORING_OFF_CQ_RING ; 
 int /*<<< orphan*/  IORING_OFF_SQES ; 
 int /*<<< orphan*/  IORING_OFF_SQ_RING ; 
 int /*<<< orphan*/  IORING_SETUP_IOPOLL ; 
 int /*<<< orphan*/  IORING_SETUP_SQPOLL ; 
 int /*<<< orphan*/  IORING_SETUP_SQ_AFF ; 
 int MAP_POPULATE ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  cq_ring_mask ; 
 int /*<<< orphan*/  do_nop ; 
 scalar_t__ fixedbufs ; 
 int io_uring_register_buffers (struct submitter*) ; 
 int io_uring_register_files (struct submitter*) ; 
 int io_uring_setup (int /*<<< orphan*/ ,struct io_uring_params*) ; 
 int /*<<< orphan*/  memset (struct io_uring_params*,int /*<<< orphan*/ ,int) ; 
 void* mmap (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ polled ; 
 int /*<<< orphan*/  printf (char*,void*) ; 
 scalar_t__ register_files ; 
 int /*<<< orphan*/  sq_ring_mask ; 
 int sq_thread_cpu ; 
 scalar_t__ sq_thread_poll ; 

__attribute__((used)) static int setup_ring(struct submitter *s)
{
	struct io_sq_ring *sring = &s->sq_ring;
	struct io_cq_ring *cring = &s->cq_ring;
	struct io_uring_params p;
	int ret, fd;
	void *ptr;

	memset(&p, 0, sizeof(p));

	if (polled && !do_nop)
		p.flags |= IORING_SETUP_IOPOLL;
	if (sq_thread_poll) {
		p.flags |= IORING_SETUP_SQPOLL;
		if (sq_thread_cpu != -1) {
			p.flags |= IORING_SETUP_SQ_AFF;
			p.sq_thread_cpu = sq_thread_cpu;
		}
	}

	fd = io_uring_setup(DEPTH, &p);
	if (fd < 0) {
		perror("io_uring_setup");
		return 1;
	}
	s->ring_fd = fd;

	if (fixedbufs) {
		ret = io_uring_register_buffers(s);
		if (ret < 0) {
			perror("io_uring_register_buffers");
			return 1;
		}
	}

	if (register_files) {
		ret = io_uring_register_files(s);
		if (ret < 0) {
			perror("io_uring_register_files");
			return 1;
		}
	}

	ptr = mmap(0, p.sq_off.array + p.sq_entries * sizeof(__u32),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
			IORING_OFF_SQ_RING);
	printf("sq_ring ptr = 0x%p\n", ptr);
	sring->head = ptr + p.sq_off.head;
	sring->tail = ptr + p.sq_off.tail;
	sring->ring_mask = ptr + p.sq_off.ring_mask;
	sring->ring_entries = ptr + p.sq_off.ring_entries;
	sring->flags = ptr + p.sq_off.flags;
	sring->array = ptr + p.sq_off.array;
	sq_ring_mask = *sring->ring_mask;

	s->sqes = mmap(0, p.sq_entries * sizeof(struct io_uring_sqe),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
			IORING_OFF_SQES);
	printf("sqes ptr    = 0x%p\n", s->sqes);

	ptr = mmap(0, p.cq_off.cqes + p.cq_entries * sizeof(struct io_uring_cqe),
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
			IORING_OFF_CQ_RING);
	printf("cq_ring ptr = 0x%p\n", ptr);
	cring->head = ptr + p.cq_off.head;
	cring->tail = ptr + p.cq_off.tail;
	cring->ring_mask = ptr + p.cq_off.ring_mask;
	cring->ring_entries = ptr + p.cq_off.ring_entries;
	cring->cqes = ptr + p.cq_off.cqes;
	cq_ring_mask = *cring->ring_mask;
	return 0;
}