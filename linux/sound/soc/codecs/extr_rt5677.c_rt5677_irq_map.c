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
struct rt5677_priv {int dummy; } ;
struct irq_domain {struct rt5677_priv* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_set_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct rt5677_priv*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (unsigned int,int) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 
 int /*<<< orphan*/  rt5677_irq_chip ; 

__attribute__((used)) static int rt5677_irq_map(struct irq_domain *h, unsigned int virq,
			  irq_hw_number_t hw)
{
	struct rt5677_priv *rt5677 = h->host_data;

	irq_set_chip_data(virq, rt5677);
	irq_set_chip(virq, &rt5677_irq_chip);
	irq_set_nested_thread(virq, 1);
	irq_set_noprobe(virq);
	return 0;
}