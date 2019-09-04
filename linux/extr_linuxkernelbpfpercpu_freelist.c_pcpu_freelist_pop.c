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
 struct pcpu_freelist_node* __pcpu_freelist_pop (struct pcpu_freelist*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

struct pcpu_freelist_node *pcpu_freelist_pop(struct pcpu_freelist *s)
{
	struct pcpu_freelist_node *ret;
	unsigned long flags;

	local_irq_save(flags);
	ret = __pcpu_freelist_pop(s);
	local_irq_restore(flags);
	return ret;
}