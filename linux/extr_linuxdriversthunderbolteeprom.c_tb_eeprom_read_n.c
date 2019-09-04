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
typedef  int u16 ;
struct tb_switch {int dummy; } ;

/* Variables and functions */
 int tb_eeprom_active (struct tb_switch*,int) ; 
 int tb_eeprom_in (struct tb_switch*,int /*<<< orphan*/ *) ; 
 int tb_eeprom_out (struct tb_switch*,int) ; 

__attribute__((used)) static int tb_eeprom_read_n(struct tb_switch *sw, u16 offset, u8 *val,
		size_t count)
{
	int i, res;
	res = tb_eeprom_active(sw, true);
	if (res)
		return res;
	res = tb_eeprom_out(sw, 3);
	if (res)
		return res;
	res = tb_eeprom_out(sw, offset >> 8);
	if (res)
		return res;
	res = tb_eeprom_out(sw, offset);
	if (res)
		return res;
	for (i = 0; i < count; i++) {
		res = tb_eeprom_in(sw, val + i);
		if (res)
			return res;
	}
	return tb_eeprom_active(sw, false);
}