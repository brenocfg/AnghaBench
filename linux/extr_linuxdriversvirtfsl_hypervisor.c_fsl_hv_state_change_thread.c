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
struct doorbell_isr {int /*<<< orphan*/  partition; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failover_subscribers ; 

__attribute__((used)) static irqreturn_t fsl_hv_state_change_thread(int irq, void *data)
{
	struct doorbell_isr *dbisr = data;

	blocking_notifier_call_chain(&failover_subscribers, dbisr->partition,
				     NULL);

	return IRQ_HANDLED;
}