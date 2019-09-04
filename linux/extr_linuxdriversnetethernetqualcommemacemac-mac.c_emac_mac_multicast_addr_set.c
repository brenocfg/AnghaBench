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
typedef  int u32 ;
struct emac_adapter {scalar_t__ base; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ EMAC_HASH_TAB_REG0 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void emac_mac_multicast_addr_set(struct emac_adapter *adpt, u8 *addr)
{
	u32 crc32, bit, reg, mta;

	/* Calculate the CRC of the MAC address */
	crc32 = ether_crc(ETH_ALEN, addr);

	/* The HASH Table is an array of 2 32-bit registers. It is
	 * treated like an array of 64 bits (BitArray[hash_value]).
	 * Use the upper 6 bits of the above CRC as the hash value.
	 */
	reg = (crc32 >> 31) & 0x1;
	bit = (crc32 >> 26) & 0x1F;

	mta = readl(adpt->base + EMAC_HASH_TAB_REG0 + (reg << 2));
	mta |= BIT(bit);
	writel(mta, adpt->base + EMAC_HASH_TAB_REG0 + (reg << 2));
}