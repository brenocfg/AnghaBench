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
typedef  int /*<<< orphan*/  u64 ;
struct netdev_hw_addr_list {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_hw_addr_list_count (struct netdev_hw_addr_list*) ; 

__attribute__((used)) static u64 rtl8187_prepare_multicast(struct ieee80211_hw *dev,
				     struct netdev_hw_addr_list *mc_list)
{
	return netdev_hw_addr_list_count(mc_list);
}