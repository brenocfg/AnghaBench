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
struct ip_set {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IPSET_MAXNAMELEN ; 
 struct ip_set* ip_set_rcu_get (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_ref_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ip_set_name_byindex(struct net *net, ip_set_id_t index, char *name)
{
	struct ip_set *set = ip_set_rcu_get(net, index);

	BUG_ON(!set);

	read_lock_bh(&ip_set_ref_lock);
	strncpy(name, set->name, IPSET_MAXNAMELEN);
	read_unlock_bh(&ip_set_ref_lock);
}