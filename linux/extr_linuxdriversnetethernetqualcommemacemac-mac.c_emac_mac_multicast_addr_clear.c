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
struct emac_adapter {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EMAC_HASH_TAB_REG0 ; 
 scalar_t__ EMAC_HASH_TAB_REG1 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void emac_mac_multicast_addr_clear(struct emac_adapter *adpt)
{
	writel(0, adpt->base + EMAC_HASH_TAB_REG0);
	writel(0, adpt->base + EMAC_HASH_TAB_REG1);
}