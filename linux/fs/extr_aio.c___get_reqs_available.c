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
struct kioctx_cpu {scalar_t__ reqs_available; } ;
struct kioctx {int req_batch; int /*<<< orphan*/  reqs_available; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct kioctx_cpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __get_reqs_available(struct kioctx *ctx)
{
	struct kioctx_cpu *kcpu;
	bool ret = false;
	unsigned long flags;

	local_irq_save(flags);
	kcpu = this_cpu_ptr(ctx->cpu);
	if (!kcpu->reqs_available) {
		int old, avail = atomic_read(&ctx->reqs_available);

		do {
			if (avail < ctx->req_batch)
				goto out;

			old = avail;
			avail = atomic_cmpxchg(&ctx->reqs_available,
					       avail, avail - ctx->req_batch);
		} while (avail != old);

		kcpu->reqs_available += ctx->req_batch;
	}

	ret = true;
	kcpu->reqs_available--;
out:
	local_irq_restore(flags);
	return ret;
}