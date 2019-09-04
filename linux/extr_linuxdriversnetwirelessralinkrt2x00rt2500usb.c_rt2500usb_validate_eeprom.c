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
struct rt2x00_dev {int /*<<< orphan*/  eeprom; } ;

/* Variables and functions */
 int ANTENNA_SW_DIVERSITY ; 
 int DEFAULT_RSSI_OFFSET ; 
 int /*<<< orphan*/  EEPROM_ANTENNA ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_DYN_TXAGC ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_HARDWARE_RADIO ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_LED_MODE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_NUM ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RF_TYPE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_TX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R17 ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R17_HIGH ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R17_LOW ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R24 ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R24_HIGH ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R24_LOW ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R25 ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R25_HIGH ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R25_LOW ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R61 ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R61_HIGH ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R61_LOW ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_THRESHOLD ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_VGC ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_VGCLOWER ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_VGCUPPER ; 
 int /*<<< orphan*/  EEPROM_CALIBRATE_OFFSET ; 
 int /*<<< orphan*/  EEPROM_CALIBRATE_OFFSET_RSSI ; 
 int /*<<< orphan*/  EEPROM_MAC_ADDR_0 ; 
 int /*<<< orphan*/  EEPROM_NIC ; 
 int /*<<< orphan*/  EEPROM_NIC_CARDBUS_ACCEL ; 
 int /*<<< orphan*/  EEPROM_NIC_CCK_TX_POWER ; 
 int /*<<< orphan*/  EEPROM_NIC_DYN_BBP_TUNE ; 
 int /*<<< orphan*/  EEPROM_SIZE ; 
 int LED_MODE_DEFAULT ; 
 int RF2522 ; 
 int rt2500usb_bbp_read (struct rt2x00_dev*,int) ; 
 int* rt2x00_eeprom_addr (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_eeprom_dbg (struct rt2x00_dev*,char*,int) ; 
 int rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_eeprom_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00lib_set_mac_address (struct rt2x00_dev*,int*) ; 
 int /*<<< orphan*/  rt2x00usb_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500usb_validate_eeprom(struct rt2x00_dev *rt2x00dev)
{
	u16 word;
	u8 *mac;
	u8 bbp;

	rt2x00usb_eeprom_read(rt2x00dev, rt2x00dev->eeprom, EEPROM_SIZE);

	/*
	 * Start validation of the data that has been read.
	 */
	mac = rt2x00_eeprom_addr(rt2x00dev, EEPROM_MAC_ADDR_0);
	rt2x00lib_set_mac_address(rt2x00dev, mac);

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_ANTENNA);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_ANTENNA_NUM, 2);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_TX_DEFAULT,
				   ANTENNA_SW_DIVERSITY);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RX_DEFAULT,
				   ANTENNA_SW_DIVERSITY);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_LED_MODE,
				   LED_MODE_DEFAULT);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_DYN_TXAGC, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_HARDWARE_RADIO, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RF_TYPE, RF2522);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_ANTENNA, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Antenna: 0x%04x\n", word);
	}

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_NIC_CARDBUS_ACCEL, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_DYN_BBP_TUNE, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CCK_TX_POWER, 0);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_NIC, word);
		rt2x00_eeprom_dbg(rt2x00dev, "NIC: 0x%04x\n", word);
	}

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_CALIBRATE_OFFSET);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_CALIBRATE_OFFSET_RSSI,
				   DEFAULT_RSSI_OFFSET);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_CALIBRATE_OFFSET, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Calibrate offset: 0x%04x\n",
				  word);
	}

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_THRESHOLD, 45);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_BBPTUNE, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune: 0x%04x\n", word);
	}

	/*
	 * Switch lower vgc bound to current BBP R17 value,
	 * lower the value a bit for better quality.
	 */
	bbp = rt2500usb_bbp_read(rt2x00dev, 17);
	bbp -= 6;

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_VGC);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_VGCUPPER, 0x40);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_VGCLOWER, bbp);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_BBPTUNE_VGC, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune vgc: 0x%04x\n", word);
	} else {
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_VGCLOWER, bbp);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_BBPTUNE_VGC, word);
	}

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_R17);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R17_LOW, 0x48);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R17_HIGH, 0x41);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_BBPTUNE_R17, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r17: 0x%04x\n", word);
	}

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_R24);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R24_LOW, 0x40);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R24_HIGH, 0x80);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_BBPTUNE_R24, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r24: 0x%04x\n", word);
	}

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_R25);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R25_LOW, 0x40);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R25_HIGH, 0x50);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_BBPTUNE_R25, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r25: 0x%04x\n", word);
	}

	word = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_R61);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R61_LOW, 0x60);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R61_HIGH, 0x6d);
		rt2x00_eeprom_write(rt2x00dev, EEPROM_BBPTUNE_R61, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r61: 0x%04x\n", word);
	}

	return 0;
}