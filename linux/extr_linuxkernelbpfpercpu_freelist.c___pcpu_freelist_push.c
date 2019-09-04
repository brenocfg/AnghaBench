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
struct pcpu_freelist_head {int dummy; } ;
struct pcpu_freelist {int /*<<< orphan*/  freelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ___pcpu_freelist_push (struct pcpu_freelist_head*,struct pcpu_freelist_node*) ; 
 struct pcpu_freelist_head* this_cpu_ptr (int /*<<< orphan*/ ) ; 

void __pcpu_freelist_push(struct pcpu_freelist *s,
			struct pcpu_freelist_node *node)
{
	struct pcpu_freelist_head *head = this_cpu_ptr(s->freelist);

	___pcpu_freelist_push(head, node);
}