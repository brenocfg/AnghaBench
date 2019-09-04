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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ODM_COMP_COMMON ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int odm_get_rf_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int,int,int,int) ; 

__attribute__((used)) static void _set_tx_a_cali_value(struct phy_dm_struct *dm, u8 rf_path,
				 u8 offset, u8 tx_a_bias_offset)
{
	u32 modi_tx_a_value = 0;
	u8 tmp1_byte = 0;
	bool is_minus = false;
	u8 comp_value = 0;

	switch (offset) {
	case 0x0:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X10124);
		break;
	case 0x1:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X10524);
		break;
	case 0x2:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X10924);
		break;
	case 0x3:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X10D24);
		break;
	case 0x4:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X30164);
		break;
	case 0x5:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X30564);
		break;
	case 0x6:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X30964);
		break;
	case 0x7:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X30D64);
		break;
	case 0x8:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X50195);
		break;
	case 0x9:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X50595);
		break;
	case 0xa:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X50995);
		break;
	case 0xb:
		odm_set_rf_reg(dm, rf_path, 0x18, 0xFFFFF, 0X50D95);
		break;
	default:
		ODM_RT_TRACE(dm, ODM_COMP_COMMON,
			     "Invalid TxA band offset...\n");
		return;
	}

	/* Get TxA value */
	modi_tx_a_value = odm_get_rf_reg(dm, rf_path, 0x61, 0xFFFFF);
	tmp1_byte = (u8)modi_tx_a_value & (BIT(3) | BIT(2) | BIT(1) | BIT(0));

	/* check how much need to calibration */
	switch (tx_a_bias_offset) {
	case 0xF6:
		is_minus = true;
		comp_value = 3;
		break;

	case 0xF4:
		is_minus = true;
		comp_value = 2;
		break;

	case 0xF2:
		is_minus = true;
		comp_value = 1;
		break;

	case 0xF3:
		is_minus = false;
		comp_value = 1;
		break;

	case 0xF5:
		is_minus = false;
		comp_value = 2;
		break;

	case 0xF7:
		is_minus = false;
		comp_value = 3;
		break;

	case 0xF9:
		is_minus = false;
		comp_value = 4;
		break;

	/* do nothing case */
	case 0xF0:
	default:
		ODM_RT_TRACE(dm, ODM_COMP_COMMON,
			     "No need to do TxA bias current calibration\n");
		return;
	}

	/* calc correct value to calibrate */
	if (is_minus) {
		if (tmp1_byte >= comp_value) {
			tmp1_byte -= comp_value;
			/*modi_tx_a_value += tmp1_byte;*/
		} else {
			tmp1_byte = 0;
		}
	} else {
		tmp1_byte += comp_value;
		if (tmp1_byte >= 7)
			tmp1_byte = 7;
	}

	/* Write back to RF reg */
	odm_set_rf_reg(dm, rf_path, 0x30, 0xFFFF,
		       (offset << 12 | (modi_tx_a_value & 0xFF0) | tmp1_byte));
}