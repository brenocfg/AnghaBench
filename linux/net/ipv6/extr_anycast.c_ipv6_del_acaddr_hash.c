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
struct ifacaddr6 {int /*<<< orphan*/  aca_addr_lst; } ;

/* Variables and functions */
 int /*<<< orphan*/  acaddr_hash_lock ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipv6_del_acaddr_hash(struct ifacaddr6 *aca)
{
	spin_lock(&acaddr_hash_lock);
	hlist_del_init_rcu(&aca->aca_addr_lst);
	spin_unlock(&acaddr_hash_lock);
}