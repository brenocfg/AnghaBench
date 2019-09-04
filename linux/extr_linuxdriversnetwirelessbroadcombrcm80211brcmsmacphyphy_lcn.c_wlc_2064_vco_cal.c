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
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIO_2064_REG056 ; 
 int /*<<< orphan*/  RADIO_2064_REG057 ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ read_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

void wlc_2064_vco_cal(struct brcms_phy *pi)
{
	u8 calnrst;

	mod_radio_reg(pi, RADIO_2064_REG057, 1 << 3, 1 << 3);
	calnrst = (u8) read_radio_reg(pi, RADIO_2064_REG056) & 0xf8;
	write_radio_reg(pi, RADIO_2064_REG056, calnrst);
	udelay(1);
	write_radio_reg(pi, RADIO_2064_REG056, calnrst | 0x03);
	udelay(1);
	write_radio_reg(pi, RADIO_2064_REG056, calnrst | 0x07);
	udelay(300);
	mod_radio_reg(pi, RADIO_2064_REG057, 1 << 3, 0);
}