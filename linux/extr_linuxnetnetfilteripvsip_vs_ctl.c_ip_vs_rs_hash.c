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
struct netns_ipvs {int /*<<< orphan*/ * rs_table; } ;
struct ip_vs_dest {int in_rs_table; int /*<<< orphan*/  d_list; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ip_vs_rs_hashkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip_vs_rs_hash(struct netns_ipvs *ipvs, struct ip_vs_dest *dest)
{
	unsigned int hash;

	if (dest->in_rs_table)
		return;

	/*
	 *	Hash by proto,addr,port,
	 *	which are the parameters of the real service.
	 */
	hash = ip_vs_rs_hashkey(dest->af, &dest->addr, dest->port);

	hlist_add_head_rcu(&dest->d_list, &ipvs->rs_table[hash]);
	dest->in_rs_table = 1;
}