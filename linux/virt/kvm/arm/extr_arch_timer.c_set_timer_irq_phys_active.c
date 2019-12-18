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
struct arch_timer_context {int /*<<< orphan*/  host_timer_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQCHIP_STATE_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int irq_set_irqchip_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void set_timer_irq_phys_active(struct arch_timer_context *ctx, bool active)
{
	int r;
	r = irq_set_irqchip_state(ctx->host_timer_irq, IRQCHIP_STATE_ACTIVE, active);
	WARN_ON(r);
}