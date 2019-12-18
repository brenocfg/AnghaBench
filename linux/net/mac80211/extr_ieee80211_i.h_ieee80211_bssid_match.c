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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int ieee80211_bssid_match(const u8 *raddr, const u8 *addr)
{
	return ether_addr_equal(raddr, addr) ||
	       is_broadcast_ether_addr(raddr);
}