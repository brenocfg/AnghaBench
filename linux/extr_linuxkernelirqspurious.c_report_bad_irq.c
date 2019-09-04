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
struct irq_desc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __report_bad_irq (struct irq_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_bad_irq(struct irq_desc *desc, irqreturn_t action_ret)
{
	static int count = 100;

	if (count > 0) {
		count--;
		__report_bad_irq(desc, action_ret);
	}
}