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
typedef  int u64 ;
struct niu {int flags; } ;

/* Variables and functions */
 int NIU_FLAGS_MCAST ; 
 int NIU_FLAGS_PROMISC ; 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int XMAC_CONFIG_HASH_FILTER_EN ; 
 int XMAC_CONFIG_PROMISCUOUS ; 
 int XMAC_CONFIG_RX_MAC_ENABLE ; 
 int nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_enable_rx_xmac(struct niu *np, int on)
{
	u64 val = nr64_mac(XMAC_CONFIG);

	val &= ~(XMAC_CONFIG_HASH_FILTER_EN |
		 XMAC_CONFIG_PROMISCUOUS);

	if (np->flags & NIU_FLAGS_MCAST)
		val |= XMAC_CONFIG_HASH_FILTER_EN;
	if (np->flags & NIU_FLAGS_PROMISC)
		val |= XMAC_CONFIG_PROMISCUOUS;

	if (on)
		val |= XMAC_CONFIG_RX_MAC_ENABLE;
	else
		val &= ~XMAC_CONFIG_RX_MAC_ENABLE;
	nw64_mac(XMAC_CONFIG, val);
}