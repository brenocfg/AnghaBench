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
struct pcpu_freelist_node {struct pcpu_freelist_node* next; } ;
struct pcpu_freelist_head {int /*<<< orphan*/  lock; struct pcpu_freelist_node* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ___pcpu_freelist_push(struct pcpu_freelist_head *head,
					 struct pcpu_freelist_node *node)
{
	raw_spin_lock(&head->lock);
	node->next = head->first;
	head->first = node;
	raw_spin_unlock(&head->lock);
}