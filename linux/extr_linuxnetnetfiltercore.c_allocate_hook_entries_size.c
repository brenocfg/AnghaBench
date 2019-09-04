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
typedef  int u16 ;
struct nf_hook_ops {int dummy; } ;
struct nf_hook_entry {int dummy; } ;
struct nf_hook_entries_rcu_head {int dummy; } ;
struct nf_hook_entries {int num_hook_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nf_hook_entries* kvzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nf_hook_entries *allocate_hook_entries_size(u16 num)
{
	struct nf_hook_entries *e;
	size_t alloc = sizeof(*e) +
		       sizeof(struct nf_hook_entry) * num +
		       sizeof(struct nf_hook_ops *) * num +
		       sizeof(struct nf_hook_entries_rcu_head);

	if (num == 0)
		return NULL;

	e = kvzalloc(alloc, GFP_KERNEL);
	if (e)
		e->num_hook_entries = num;
	return e;
}