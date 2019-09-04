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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _set_tx_a_cali_value (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void _txa_bias_cali_4_each_path(struct phy_dm_struct *dm, u8 rf_path,
				       u8 efuse_value)
{
	/* switch on set TxA bias */
	odm_set_rf_reg(dm, rf_path, 0xEF, 0xFFFFF, 0x200);

	/* Set 12 sets of TxA value */
	_set_tx_a_cali_value(dm, rf_path, 0x0, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x1, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x2, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x3, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x4, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x5, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x6, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x7, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x8, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0x9, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0xa, efuse_value);
	_set_tx_a_cali_value(dm, rf_path, 0xb, efuse_value);

	/* switch off set TxA bias */
	odm_set_rf_reg(dm, rf_path, 0xEF, 0xFFFFF, 0x0);
}