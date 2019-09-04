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
struct electra_cf_socket {int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  electra_cf_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t electra_cf_irq(int irq, void *_cf)
{
	struct electra_cf_socket *cf = _cf;

	electra_cf_timer(&cf->timer);
	return IRQ_HANDLED;
}