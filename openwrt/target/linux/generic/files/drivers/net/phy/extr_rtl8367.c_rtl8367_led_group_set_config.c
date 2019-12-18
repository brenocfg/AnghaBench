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
typedef  unsigned int u16 ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RMW (struct rtl8366_smi*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int RTL8367_LED_CONFIG_LED_CFG_M ; 
 int /*<<< orphan*/  RTL8367_LED_CONFIG_REG ; 
 unsigned int RTL8367_LED_CONFIG_SEL ; 

__attribute__((used)) static int rtl8367_led_group_set_config(struct rtl8366_smi *smi,
				        unsigned int led, unsigned int cfg)
{
	u16 mask;
	u16 set;
	int err;

	mask = (RTL8367_LED_CONFIG_LED_CFG_M << (led * 4)) |
		RTL8367_LED_CONFIG_SEL;
	set = (cfg & RTL8367_LED_CONFIG_LED_CFG_M) << (led * 4);

	REG_RMW(smi, RTL8367_LED_CONFIG_REG, mask, set);
	return 0;
}