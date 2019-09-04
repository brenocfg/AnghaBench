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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u16 ;
struct tb_switch {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ tb_crc8 (scalar_t__*,int) ; 
 int tb_eeprom_get_drom_offset (struct tb_switch*,scalar_t__*) ; 
 int tb_eeprom_read_n (struct tb_switch*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*,scalar_t__,scalar_t__) ; 

int tb_drom_read_uid_only(struct tb_switch *sw, u64 *uid)
{
	u8 data[9];
	u16 drom_offset;
	u8 crc;
	int res = tb_eeprom_get_drom_offset(sw, &drom_offset);
	if (res)
		return res;

	if (drom_offset == 0)
		return -ENODEV;

	/* read uid */
	res = tb_eeprom_read_n(sw, drom_offset, data, 9);
	if (res)
		return res;

	crc = tb_crc8(data + 1, 8);
	if (crc != data[0]) {
		tb_sw_warn(sw, "uid crc8 mismatch (expected: %#x, got: %#x)\n",
				data[0], crc);
		return -EIO;
	}

	*uid = *(u64 *)(data+1);
	return 0;
}