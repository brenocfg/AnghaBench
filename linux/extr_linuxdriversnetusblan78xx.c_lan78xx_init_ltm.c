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
typedef  int u8 ;
typedef  int u32 ;
struct lan78xx_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTM_BELT_ACT0 ; 
 int /*<<< orphan*/  LTM_BELT_ACT1 ; 
 int /*<<< orphan*/  LTM_BELT_IDLE0 ; 
 int /*<<< orphan*/  LTM_BELT_IDLE1 ; 
 int /*<<< orphan*/  LTM_INACTIVE0 ; 
 int /*<<< orphan*/  LTM_INACTIVE1 ; 
 int /*<<< orphan*/  USB_CFG1 ; 
 int USB_CFG1_LTM_ENABLE_ ; 
 scalar_t__ lan78xx_read_eeprom (struct lan78xx_net*,int,int,int*) ; 
 scalar_t__ lan78xx_read_otp (struct lan78xx_net*,int,int,int*) ; 
 int lan78xx_read_raw_eeprom (struct lan78xx_net*,int,int,int*) ; 
 int lan78xx_read_raw_otp (struct lan78xx_net*,int,int,int*) ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan78xx_init_ltm(struct lan78xx_net *dev)
{
	int ret;
	u32 buf;
	u32 regs[6] = { 0 };

	ret = lan78xx_read_reg(dev, USB_CFG1, &buf);
	if (buf & USB_CFG1_LTM_ENABLE_) {
		u8 temp[2];
		/* Get values from EEPROM first */
		if (lan78xx_read_eeprom(dev, 0x3F, 2, temp) == 0) {
			if (temp[0] == 24) {
				ret = lan78xx_read_raw_eeprom(dev,
							      temp[1] * 2,
							      24,
							      (u8 *)regs);
				if (ret < 0)
					return;
			}
		} else if (lan78xx_read_otp(dev, 0x3F, 2, temp) == 0) {
			if (temp[0] == 24) {
				ret = lan78xx_read_raw_otp(dev,
							   temp[1] * 2,
							   24,
							   (u8 *)regs);
				if (ret < 0)
					return;
			}
		}
	}

	lan78xx_write_reg(dev, LTM_BELT_IDLE0, regs[0]);
	lan78xx_write_reg(dev, LTM_BELT_IDLE1, regs[1]);
	lan78xx_write_reg(dev, LTM_BELT_ACT0, regs[2]);
	lan78xx_write_reg(dev, LTM_BELT_ACT1, regs[3]);
	lan78xx_write_reg(dev, LTM_INACTIVE0, regs[4]);
	lan78xx_write_reg(dev, LTM_INACTIVE1, regs[5]);
}