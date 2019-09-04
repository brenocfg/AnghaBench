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
struct phy_dm_struct {int* band_type; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int BIT (int) ; 
#define  ODM_BAND_2_4G 129 
#define  ODM_BAND_5G 128 
 int RFREGOFFSETMASK ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int,int,int,int) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_lok_setting_8822b(struct phy_dm_struct *dm, u8 path)
{
	odm_write_4byte(dm, 0x1b00, 0xf8000008 | path << 1);
	odm_write_4byte(dm, 0x1bcc, 0x9);
	odm_write_1byte(dm, 0x1b23, 0x00);

	switch (*dm->band_type) {
	case ODM_BAND_2_4G:
		odm_write_1byte(dm, 0x1b2b, 0x00);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x56,
			       RFREGOFFSETMASK, 0x50df2);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x8f,
			       RFREGOFFSETMASK, 0xadc00);
		/* WE_LUT_TX_LOK*/
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0xef, BIT(4),
			       0x1);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x33,
			       BIT(1) | BIT(0), 0x0);
		break;
	case ODM_BAND_5G:
		odm_write_1byte(dm, 0x1b2b, 0x80);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x56,
			       RFREGOFFSETMASK, 0x5086c);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x8f,
			       RFREGOFFSETMASK, 0xa9c00);
		/* WE_LUT_TX_LOK*/
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0xef, BIT(4),
			       0x1);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x33,
			       BIT(1) | BIT(0), 0x1);
		break;
	}
}