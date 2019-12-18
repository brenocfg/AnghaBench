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
struct net {int dummy; } ;
struct ifacaddr6 {int /*<<< orphan*/  aca_addr_lst; int /*<<< orphan*/  aca_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  acaddr_hash_lock ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int inet6_acaddr_hash (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * inet6_acaddr_lst ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipv6_add_acaddr_hash(struct net *net, struct ifacaddr6 *aca)
{
	unsigned int hash = inet6_acaddr_hash(net, &aca->aca_addr);

	spin_lock(&acaddr_hash_lock);
	hlist_add_head_rcu(&aca->aca_addr_lst, &inet6_acaddr_lst[hash]);
	spin_unlock(&acaddr_hash_lock);
}