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
typedef  int u16 ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RMW (struct rtl8366_smi*,int,int,int) ; 
 int RTL8367_PARA_LED_IO_EN1_REG ; 
 int RTL8367_PARA_LED_IO_EN_PMASK ; 

__attribute__((used)) static int rtl8367_led_group_set_ports(struct rtl8366_smi *smi,
				       unsigned int group, u16 port_mask)
{
	u32 reg;
	u32 s;
	int err;

	port_mask &= RTL8367_PARA_LED_IO_EN_PMASK;
	s = (group % 2) * 8;
	reg = RTL8367_PARA_LED_IO_EN1_REG + (group / 2);

	REG_RMW(smi, reg, (RTL8367_PARA_LED_IO_EN_PMASK << s), port_mask << s);

	return 0;
}