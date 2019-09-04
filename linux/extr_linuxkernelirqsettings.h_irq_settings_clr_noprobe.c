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
struct irq_desc {int /*<<< orphan*/  status_use_accessors; } ;

/* Variables and functions */
 int /*<<< orphan*/  _IRQ_NOPROBE ; 

__attribute__((used)) static inline void irq_settings_clr_noprobe(struct irq_desc *desc)
{
	desc->status_use_accessors &= ~_IRQ_NOPROBE;
}