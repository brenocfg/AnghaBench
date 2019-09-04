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
typedef  int u16 ;
struct rt2x00_dev {int /*<<< orphan*/  flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CHANNEL_HT40 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_DELTA ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_DELTA_ENABLE_2G ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_DELTA_ENABLE_5G ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_DELTA_TYPE_2G ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_DELTA_TYPE_5G ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_DELTA_VALUE_2G ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_DELTA_VALUE_5G ; 
 int NL80211_BAND_2GHZ ; 
 int rt2800_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt2800_get_txpower_bw_comp(struct rt2x00_dev *rt2x00dev,
				      enum nl80211_band band)
{
	u16 eeprom;
	u8 comp_en;
	u8 comp_type;
	int comp_value = 0;

	eeprom = rt2800_eeprom_read(rt2x00dev, EEPROM_TXPOWER_DELTA);

	/*
	 * HT40 compensation not required.
	 */
	if (eeprom == 0xffff ||
	    !test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags))
		return 0;

	if (band == NL80211_BAND_2GHZ) {
		comp_en = rt2x00_get_field16(eeprom,
				 EEPROM_TXPOWER_DELTA_ENABLE_2G);
		if (comp_en) {
			comp_type = rt2x00_get_field16(eeprom,
					   EEPROM_TXPOWER_DELTA_TYPE_2G);
			comp_value = rt2x00_get_field16(eeprom,
					    EEPROM_TXPOWER_DELTA_VALUE_2G);
			if (!comp_type)
				comp_value = -comp_value;
		}
	} else {
		comp_en = rt2x00_get_field16(eeprom,
				 EEPROM_TXPOWER_DELTA_ENABLE_5G);
		if (comp_en) {
			comp_type = rt2x00_get_field16(eeprom,
					   EEPROM_TXPOWER_DELTA_TYPE_5G);
			comp_value = rt2x00_get_field16(eeprom,
					    EEPROM_TXPOWER_DELTA_VALUE_5G);
			if (!comp_type)
				comp_value = -comp_value;
		}
	}

	return comp_value;
}