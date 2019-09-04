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
 int /*<<< orphan*/  BRXMAC_CONFIG ; 
 int BRXMAC_CONFIG_ENABLE ; 
 int BRXMAC_CONFIG_HASH_FILT_EN ; 
 int BRXMAC_CONFIG_PROMISC ; 
 int NIU_FLAGS_MCAST ; 
 int NIU_FLAGS_PROMISC ; 
 int nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_enable_rx_bmac(struct niu *np, int on)
{
	u64 val = nr64_mac(BRXMAC_CONFIG);

	val &= ~(BRXMAC_CONFIG_HASH_FILT_EN |
		 BRXMAC_CONFIG_PROMISC);

	if (np->flags & NIU_FLAGS_MCAST)
		val |= BRXMAC_CONFIG_HASH_FILT_EN;
	if (np->flags & NIU_FLAGS_PROMISC)
		val |= BRXMAC_CONFIG_PROMISC;

	if (on)
		val |= BRXMAC_CONFIG_ENABLE;
	else
		val &= ~BRXMAC_CONFIG_ENABLE;
	nw64_mac(BRXMAC_CONFIG, val);
}