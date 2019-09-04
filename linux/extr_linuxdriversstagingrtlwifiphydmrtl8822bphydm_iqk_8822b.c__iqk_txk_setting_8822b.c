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
#define  ODM_BAND_2_4G 129 
#define  ODM_BAND_5G 128 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_txk_setting_8822b(struct phy_dm_struct *dm, u8 path)
{
	odm_write_4byte(dm, 0x1b00, 0xf8000008 | path << 1);
	odm_write_4byte(dm, 0x1bcc, 0x9);
	odm_write_4byte(dm, 0x1b20, 0x01440008);

	if (path == 0x0)
		odm_write_4byte(dm, 0x1b00, 0xf800000a);
	else
		odm_write_4byte(dm, 0x1b00, 0xf8000008);
	odm_write_4byte(dm, 0x1bcc, 0x3f);

	switch (*dm->band_type) {
	case ODM_BAND_2_4G:
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x56,
			       RFREGOFFSETMASK, 0x50df2);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x8f,
			       RFREGOFFSETMASK, 0xadc00);
		odm_write_1byte(dm, 0x1b2b, 0x00);
		break;
	case ODM_BAND_5G:
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x56,
			       RFREGOFFSETMASK, 0x500ef);
		odm_set_rf_reg(dm, (enum odm_rf_radio_path)path, 0x8f,
			       RFREGOFFSETMASK, 0xa9c00);
		odm_write_1byte(dm, 0x1b2b, 0x80);
		break;
	}
}