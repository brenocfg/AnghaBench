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
typedef  unsigned int irqreturn_t ;

/* Variables and functions */
 unsigned int IRQ_HANDLED ; 
 unsigned int IRQ_WAKE_THREAD ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int bad_action_ret(irqreturn_t action_ret)
{
	unsigned int r = action_ret;

	if (likely(r <= (IRQ_HANDLED | IRQ_WAKE_THREAD)))
		return 0;
	return 1;
}