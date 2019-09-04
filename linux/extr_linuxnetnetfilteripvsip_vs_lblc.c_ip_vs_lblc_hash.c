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
struct ip_vs_lblc_table {int /*<<< orphan*/  entries; int /*<<< orphan*/ * bucket; } ;
struct ip_vs_lblc_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ip_vs_lblc_hashkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip_vs_lblc_hash(struct ip_vs_lblc_table *tbl, struct ip_vs_lblc_entry *en)
{
	unsigned int hash = ip_vs_lblc_hashkey(en->af, &en->addr);

	hlist_add_head_rcu(&en->list, &tbl->bucket[hash]);
	atomic_inc(&tbl->entries);
}