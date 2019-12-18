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
struct hlist_node {int /*<<< orphan*/  next; } ;
struct hlist_head {int /*<<< orphan*/  first; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 struct hlist_node* rcu_dereference (int /*<<< orphan*/ ) ; 

struct hlist_node *seq_hlist_next_rcu(void *v,
				      struct hlist_head *head,
				      loff_t *ppos)
{
	struct hlist_node *node = v;

	++*ppos;
	if (v == SEQ_START_TOKEN)
		return rcu_dereference(head->first);
	else
		return rcu_dereference(node->next);
}