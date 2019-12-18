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
typedef  int u32 ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RMW (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL8366S_GREEN_ETHERNET_CTRL_MASK ; 
 int /*<<< orphan*/  RTL8366S_GREEN_ETHERNET_CTRL_REG ; 
 int RTL8366S_GREEN_ETHERNET_RX_BIT ; 
 int RTL8366S_GREEN_ETHERNET_TX_BIT ; 
 unsigned int RTL8366S_PHY_NO_MAX ; 
 int /*<<< orphan*/  rtl8366s_set_green_port (struct rtl8366_smi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366s_set_green(struct rtl8366_smi *smi, int enable)
{
	int err;
	unsigned i;
	u32 data = 0;

	if (!enable) {
		for (i = 0; i <= RTL8366S_PHY_NO_MAX; i++) {
			rtl8366s_set_green_port(smi, i, 0);
		}
	}

	if (enable)
		data = (RTL8366S_GREEN_ETHERNET_TX_BIT | RTL8366S_GREEN_ETHERNET_RX_BIT);

	REG_RMW(smi, RTL8366S_GREEN_ETHERNET_CTRL_REG, RTL8366S_GREEN_ETHERNET_CTRL_MASK, data);

	return 0;
}