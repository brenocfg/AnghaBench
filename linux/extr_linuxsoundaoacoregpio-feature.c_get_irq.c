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
struct device_node {int dummy; } ;

/* Variables and functions */
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_irq(struct device_node * np, int *irqptr)
{
	if (np)
		*irqptr = irq_of_parse_and_map(np, 0);
	else
		*irqptr = 0;
}