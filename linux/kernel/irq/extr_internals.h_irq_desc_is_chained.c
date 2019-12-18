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
struct irq_desc {int /*<<< orphan*/ * action; } ;

/* Variables and functions */
 int /*<<< orphan*/  chained_action ; 

__attribute__((used)) static inline int irq_desc_is_chained(struct irq_desc *desc)
{
	return (desc->action && desc->action == &chained_action);
}