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
struct tb_switch {int dummy; } ;
struct tb_eeprom_ctl {int data_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_EEPROM_OUT ; 
 int tb_eeprom_ctl_read (struct tb_switch*,struct tb_eeprom_ctl*) ; 
 int tb_eeprom_transfer (struct tb_switch*,struct tb_eeprom_ctl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_eeprom_out(struct tb_switch *sw, u8 val)
{
	struct tb_eeprom_ctl ctl;
	int i;
	int res = tb_eeprom_ctl_read(sw, &ctl);
	if (res)
		return res;
	for (i = 0; i < 8; i++) {
		ctl.data_out = val & 0x80;
		res = tb_eeprom_transfer(sw, &ctl, TB_EEPROM_OUT);
		if (res)
			return res;
		val <<= 1;
	}
	return 0;
}