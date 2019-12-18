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
struct kioctx_cpu {int reqs_available; } ;
struct kioctx {int req_batch; int /*<<< orphan*/  reqs_available; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct kioctx_cpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_reqs_available(struct kioctx *ctx, unsigned nr)
{
	struct kioctx_cpu *kcpu;
	unsigned long flags;

	local_irq_save(flags);
	kcpu = this_cpu_ptr(ctx->cpu);
	kcpu->reqs_available += nr;

	while (kcpu->reqs_available >= ctx->req_batch * 2) {
		kcpu->reqs_available -= ctx->req_batch;
		atomic_add(ctx->req_batch, &ctx->reqs_available);
	}

	local_irq_restore(flags);
}