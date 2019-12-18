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

/* Variables and functions */
 int /*<<< orphan*/  __irq_disable (struct irq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_settings_disable_unlazy (struct irq_desc*) ; 

void irq_disable(struct irq_desc *desc)
{
	__irq_disable(desc, irq_settings_disable_unlazy(desc));
}