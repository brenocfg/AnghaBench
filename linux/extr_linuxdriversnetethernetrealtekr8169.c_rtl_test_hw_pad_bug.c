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
struct sk_buff {scalar_t__ len; } ;
struct rtl8169_private {scalar_t__ mac_version; } ;

/* Variables and functions */
 scalar_t__ ETH_ZLEN ; 
 scalar_t__ RTL_GIGA_MAC_VER_34 ; 

__attribute__((used)) static bool rtl_test_hw_pad_bug(struct rtl8169_private *tp, struct sk_buff *skb)
{
	return skb->len < ETH_ZLEN && tp->mac_version == RTL_GIGA_MAC_VER_34;
}