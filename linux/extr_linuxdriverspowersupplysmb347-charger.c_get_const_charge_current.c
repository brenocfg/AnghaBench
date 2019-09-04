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
struct smb347_charger {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODATA ; 
 int /*<<< orphan*/  STAT_B ; 
 int /*<<< orphan*/  fcc_tbl ; 
 int hw_to_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pcc_tbl ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  smb347_is_ps_online (struct smb347_charger*) ; 

__attribute__((used)) static int get_const_charge_current(struct smb347_charger *smb)
{
	int ret, intval;
	unsigned int v;

	if (!smb347_is_ps_online(smb))
		return -ENODATA;

	ret = regmap_read(smb->regmap, STAT_B, &v);
	if (ret < 0)
		return ret;

	/*
	 * The current value is composition of FCC and PCC values
	 * and we can detect which table to use from bit 5.
	 */
	if (v & 0x20) {
		intval = hw_to_current(fcc_tbl, ARRAY_SIZE(fcc_tbl), v & 7);
	} else {
		v >>= 3;
		intval = hw_to_current(pcc_tbl, ARRAY_SIZE(pcc_tbl), v & 7);
	}

	return intval;
}