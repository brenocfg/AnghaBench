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
typedef  size_t u32 ;
struct net {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  hash; int /*<<< orphan*/  ifa_local; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t inet_addr_hash (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_addr_lst ; 

__attribute__((used)) static void inet_hash_insert(struct net *net, struct in_ifaddr *ifa)
{
	u32 hash = inet_addr_hash(net, ifa->ifa_local);

	ASSERT_RTNL();
	hlist_add_head_rcu(&ifa->hash, &inet_addr_lst[hash]);
}