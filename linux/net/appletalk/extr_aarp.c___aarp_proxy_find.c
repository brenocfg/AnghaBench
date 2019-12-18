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
struct aarp_entry {int dummy; } ;

/* Variables and functions */
 int AARP_HASH_SIZE ; 
 struct aarp_entry* __aarp_find_entry (int /*<<< orphan*/ ,struct net_device*,struct atalk_addr*) ; 
 int /*<<< orphan*/ * proxies ; 

__attribute__((used)) static struct atalk_addr *__aarp_proxy_find(struct net_device *dev,
					    struct atalk_addr *sa)
{
	int hash = sa->s_node % (AARP_HASH_SIZE - 1);
	struct aarp_entry *a = __aarp_find_entry(proxies[hash], dev, sa);

	return a ? sa : NULL;
}