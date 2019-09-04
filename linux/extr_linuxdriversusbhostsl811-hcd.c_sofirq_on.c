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
struct sl811 {int irq_enable; } ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int SL11H_INTMASK_SOFINTR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* sl811_to_hcd (struct sl811*) ; 

__attribute__((used)) static inline void sofirq_on(struct sl811 *sl811)
{
	if (sl811->irq_enable & SL11H_INTMASK_SOFINTR)
		return;
	dev_dbg(sl811_to_hcd(sl811)->self.controller, "sof irq on\n");
	sl811->irq_enable |= SL11H_INTMASK_SOFINTR;
}