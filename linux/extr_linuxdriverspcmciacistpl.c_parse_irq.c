#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_3__ {int IRQInfo1; int IRQInfo2; } ;
typedef  TYPE_1__ cistpl_irq_t ;

/* Variables and functions */
 int IRQ_INFO2_VALID ; 

__attribute__((used)) static u_char *parse_irq(u_char *p, u_char *q, cistpl_irq_t *irq)
{
	if (p == q)
		return NULL;
	irq->IRQInfo1 = *p; p++;
	if (irq->IRQInfo1 & IRQ_INFO2_VALID) {
		if (p+2 > q)
			return NULL;
		irq->IRQInfo2 = (p[1]<<8) + p[0];
		p += 2;
	}
	return p;
}