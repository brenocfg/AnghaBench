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
struct pcpu_freelist_node {int dummy; } ;
struct pcpu_freelist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pcpu_freelist_push (struct pcpu_freelist*,struct pcpu_freelist_node*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void pcpu_freelist_push(struct pcpu_freelist *s,
			struct pcpu_freelist_node *node)
{
	unsigned long flags;

	local_irq_save(flags);
	__pcpu_freelist_push(s, node);
	local_irq_restore(flags);
}