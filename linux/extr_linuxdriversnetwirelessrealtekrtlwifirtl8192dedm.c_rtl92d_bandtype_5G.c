#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int* ofdm_index; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct rtl_phy {int current_channel; } ;
struct rtl_hal {scalar_t__ macphymode; int interfaceindex; } ;
struct rtl_efuse {int* internal_pa_5g; int eeprom_thermalmeter; } ;

/* Variables and functions */
 scalar_t__ DUALMAC_DUALPHY ; 
 int INDEX_MAPPING_NUM ; 

__attribute__((used)) static void rtl92d_bandtype_5G(struct rtl_hal *rtlhal, u8 *ofdm_index,
			       bool *internal_pa, u8 thermalvalue, u8 delta,
			       u8 rf, struct rtl_efuse *rtlefuse,
			       struct rtl_priv *rtlpriv, struct rtl_phy *rtlphy,
			       u8 index_mapping[5][INDEX_MAPPING_NUM],
			       u8 index_mapping_pa[8][INDEX_MAPPING_NUM])
{
	int i;
	u8 index;
	u8 offset = 0;

	for (i = 0; i < rf; i++) {
		if (rtlhal->macphymode == DUALMAC_DUALPHY &&
		    rtlhal->interfaceindex == 1)	/* MAC 1 5G */
			*internal_pa = rtlefuse->internal_pa_5g[1];
		else
			*internal_pa = rtlefuse->internal_pa_5g[i];
		if (*internal_pa) {
			if (rtlhal->interfaceindex == 1 || i == rf)
				offset = 4;
			else
				offset = 0;
			if (rtlphy->current_channel >= 100 &&
				rtlphy->current_channel <= 165)
				offset += 2;
		} else {
			if (rtlhal->interfaceindex == 1 || i == rf)
				offset = 2;
			else
				offset = 0;
		}
		if (thermalvalue > rtlefuse->eeprom_thermalmeter)
			offset++;
		if (*internal_pa) {
			if (delta > INDEX_MAPPING_NUM - 1)
				index = index_mapping_pa[offset]
						    [INDEX_MAPPING_NUM - 1];
			else
				index =
				     index_mapping_pa[offset][delta];
		} else {
			if (delta > INDEX_MAPPING_NUM - 1)
				index =
				   index_mapping[offset][INDEX_MAPPING_NUM - 1];
			else
				index = index_mapping[offset][delta];
		}
		if (thermalvalue > rtlefuse->eeprom_thermalmeter) {
			if (*internal_pa && thermalvalue > 0x12) {
				ofdm_index[i] = rtlpriv->dm.ofdm_index[i] -
						((delta / 2) * 3 + (delta % 2));
			} else {
				ofdm_index[i] -= index;
			}
		} else {
			ofdm_index[i] += index;
		}
	}
}