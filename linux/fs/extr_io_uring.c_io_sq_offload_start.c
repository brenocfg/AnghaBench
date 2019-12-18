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
struct io_uring_params {int flags; int sq_thread_cpu; int /*<<< orphan*/  sq_thread_idle; } ;
struct io_ring_ctx {int flags; int /*<<< orphan*/ * sqo_mm; void** sqo_wq; scalar_t__ sq_entries; int /*<<< orphan*/ * sqo_thread; scalar_t__ sq_thread_idle; int /*<<< orphan*/  sqo_wait; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ HZ ; 
 int IORING_SETUP_SQPOLL ; 
 int IORING_SETUP_SQ_AFF ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int WQ_FREEZABLE ; 
 int WQ_UNBOUND ; 
 void* alloc_workqueue (char*,int,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_finish_async (struct io_ring_ctx*) ; 
 int /*<<< orphan*/  io_sq_thread ; 
 int /*<<< orphan*/ * kthread_create (int /*<<< orphan*/ ,struct io_ring_ctx*,char*) ; 
 int /*<<< orphan*/ * kthread_create_on_cpu (int /*<<< orphan*/ ,struct io_ring_ctx*,int,char*) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ *) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_sq_offload_start(struct io_ring_ctx *ctx,
			       struct io_uring_params *p)
{
	int ret;

	init_waitqueue_head(&ctx->sqo_wait);
	mmgrab(current->mm);
	ctx->sqo_mm = current->mm;

	if (ctx->flags & IORING_SETUP_SQPOLL) {
		ret = -EPERM;
		if (!capable(CAP_SYS_ADMIN))
			goto err;

		ctx->sq_thread_idle = msecs_to_jiffies(p->sq_thread_idle);
		if (!ctx->sq_thread_idle)
			ctx->sq_thread_idle = HZ;

		if (p->flags & IORING_SETUP_SQ_AFF) {
			int cpu = p->sq_thread_cpu;

			ret = -EINVAL;
			if (cpu >= nr_cpu_ids)
				goto err;
			if (!cpu_online(cpu))
				goto err;

			ctx->sqo_thread = kthread_create_on_cpu(io_sq_thread,
							ctx, cpu,
							"io_uring-sq");
		} else {
			ctx->sqo_thread = kthread_create(io_sq_thread, ctx,
							"io_uring-sq");
		}
		if (IS_ERR(ctx->sqo_thread)) {
			ret = PTR_ERR(ctx->sqo_thread);
			ctx->sqo_thread = NULL;
			goto err;
		}
		wake_up_process(ctx->sqo_thread);
	} else if (p->flags & IORING_SETUP_SQ_AFF) {
		/* Can't have SQ_AFF without SQPOLL */
		ret = -EINVAL;
		goto err;
	}

	/* Do QD, or 2 * CPUS, whatever is smallest */
	ctx->sqo_wq[0] = alloc_workqueue("io_ring-wq",
			WQ_UNBOUND | WQ_FREEZABLE,
			min(ctx->sq_entries - 1, 2 * num_online_cpus()));
	if (!ctx->sqo_wq[0]) {
		ret = -ENOMEM;
		goto err;
	}

	/*
	 * This is for buffered writes, where we want to limit the parallelism
	 * due to file locking in file systems. As "normal" buffered writes
	 * should parellelize on writeout quite nicely, limit us to having 2
	 * pending. This avoids massive contention on the inode when doing
	 * buffered async writes.
	 */
	ctx->sqo_wq[1] = alloc_workqueue("io_ring-write-wq",
						WQ_UNBOUND | WQ_FREEZABLE, 2);
	if (!ctx->sqo_wq[1]) {
		ret = -ENOMEM;
		goto err;
	}

	return 0;
err:
	io_finish_async(ctx);
	mmdrop(ctx->sqo_mm);
	ctx->sqo_mm = NULL;
	return ret;
}