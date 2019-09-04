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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct emac_adapter {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EMAC_MAC_STA_ADDR0 ; 
 scalar_t__ EMAC_MAC_STA_ADDR1 ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void emac_set_mac_address(struct emac_adapter *adpt, u8 *addr)
{
	u32 sta;

	/* for example: 00-A0-C6-11-22-33
	 * 0<-->C6112233, 1<-->00A0.
	 */

	/* low 32bit word */
	sta = (((u32)addr[2]) << 24) | (((u32)addr[3]) << 16) |
	      (((u32)addr[4]) << 8)  | (((u32)addr[5]));
	writel(sta, adpt->base + EMAC_MAC_STA_ADDR0);

	/* hight 32bit word */
	sta = (((u32)addr[0]) << 8) | (u32)addr[1];
	writel(sta, adpt->base + EMAC_MAC_STA_ADDR1);
}