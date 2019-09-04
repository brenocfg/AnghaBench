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
struct ip_vs_lblc_entry {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_lblc_rcu_free ; 

__attribute__((used)) static inline void ip_vs_lblc_del(struct ip_vs_lblc_entry *en)
{
	hlist_del_rcu(&en->list);
	call_rcu(&en->rcu_head, ip_vs_lblc_rcu_free);
}