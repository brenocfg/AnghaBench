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
struct nf_hook_ops {int dummy; } ;
struct nf_hook_entries_rcu_head {int /*<<< orphan*/  head; struct nf_hook_entries* allocation; } ;
struct nf_hook_entries {unsigned int num_hook_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nf_hook_entries_free ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nf_hook_ops** nf_hook_entries_get_hook_ops (struct nf_hook_entries*) ; 

__attribute__((used)) static void nf_hook_entries_free(struct nf_hook_entries *e)
{
	struct nf_hook_entries_rcu_head *head;
	struct nf_hook_ops **ops;
	unsigned int num;

	if (!e)
		return;

	num = e->num_hook_entries;
	ops = nf_hook_entries_get_hook_ops(e);
	head = (void *)&ops[num];
	head->allocation = e;
	call_rcu(&head->head, __nf_hook_entries_free);
}