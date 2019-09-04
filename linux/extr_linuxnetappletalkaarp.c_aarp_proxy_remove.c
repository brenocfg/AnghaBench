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
struct net_device {int dummy; } ;
struct atalk_addr {int s_node; } ;
struct aarp_entry {scalar_t__ expires_at; } ;

/* Variables and functions */
 int AARP_HASH_SIZE ; 
 struct aarp_entry* __aarp_find_entry (int /*<<< orphan*/ ,struct net_device*,struct atalk_addr*) ; 
 int /*<<< orphan*/  aarp_lock ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * proxies ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void aarp_proxy_remove(struct net_device *dev, struct atalk_addr *sa)
{
	int hash = sa->s_node % (AARP_HASH_SIZE - 1);
	struct aarp_entry *a;

	write_lock_bh(&aarp_lock);

	a = __aarp_find_entry(proxies[hash], dev, sa);
	if (a)
		a->expires_at = jiffies - 1;

	write_unlock_bh(&aarp_lock);
}