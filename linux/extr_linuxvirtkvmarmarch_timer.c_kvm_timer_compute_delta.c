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
typedef  scalar_t__ u64 ;
struct arch_timer_context {scalar_t__ cnt_cval; scalar_t__ cntvoff; } ;
struct TYPE_2__ {int /*<<< orphan*/  frac; int /*<<< orphan*/  mask; int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 scalar_t__ cyclecounter_cyc2ns (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_phys_timer_read () ; 
 TYPE_1__* timecounter ; 

__attribute__((used)) static u64 kvm_timer_compute_delta(struct arch_timer_context *timer_ctx)
{
	u64 cval, now;

	cval = timer_ctx->cnt_cval;
	now = kvm_phys_timer_read() - timer_ctx->cntvoff;

	if (now < cval) {
		u64 ns;

		ns = cyclecounter_cyc2ns(timecounter->cc,
					 cval - now,
					 timecounter->mask,
					 &timecounter->frac);
		return ns;
	}

	return 0;
}