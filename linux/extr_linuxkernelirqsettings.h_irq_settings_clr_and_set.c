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
typedef  int u32 ;
struct irq_desc {int status_use_accessors; } ;

/* Variables and functions */
 int _IRQF_MODIFY_MASK ; 

__attribute__((used)) static inline void
irq_settings_clr_and_set(struct irq_desc *desc, u32 clr, u32 set)
{
	desc->status_use_accessors &= ~(clr & _IRQF_MODIFY_MASK);
	desc->status_use_accessors |= (set & _IRQF_MODIFY_MASK);
}