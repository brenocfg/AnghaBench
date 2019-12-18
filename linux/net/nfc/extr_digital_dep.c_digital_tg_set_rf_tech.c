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
struct nfc_digital_dev {int curr_rf_tech; int /*<<< orphan*/  skb_check_crc; int /*<<< orphan*/  skb_add_crc; } ;

/* Variables and functions */
 scalar_t__ DIGITAL_DRV_CAPS_TG_CRC (struct nfc_digital_dev*) ; 
#define  NFC_DIGITAL_RF_TECH_106A 130 
#define  NFC_DIGITAL_RF_TECH_212F 129 
#define  NFC_DIGITAL_RF_TECH_424F 128 
 int /*<<< orphan*/  digital_skb_add_crc_a ; 
 int /*<<< orphan*/  digital_skb_add_crc_f ; 
 int /*<<< orphan*/  digital_skb_add_crc_none ; 
 int /*<<< orphan*/  digital_skb_check_crc_a ; 
 int /*<<< orphan*/  digital_skb_check_crc_f ; 
 int /*<<< orphan*/  digital_skb_check_crc_none ; 

__attribute__((used)) static void digital_tg_set_rf_tech(struct nfc_digital_dev *ddev, u8 rf_tech)
{
	ddev->curr_rf_tech = rf_tech;

	ddev->skb_add_crc = digital_skb_add_crc_none;
	ddev->skb_check_crc = digital_skb_check_crc_none;

	if (DIGITAL_DRV_CAPS_TG_CRC(ddev))
		return;

	switch (ddev->curr_rf_tech) {
	case NFC_DIGITAL_RF_TECH_106A:
		ddev->skb_add_crc = digital_skb_add_crc_a;
		ddev->skb_check_crc = digital_skb_check_crc_a;
		break;

	case NFC_DIGITAL_RF_TECH_212F:
	case NFC_DIGITAL_RF_TECH_424F:
		ddev->skb_add_crc = digital_skb_add_crc_f;
		ddev->skb_check_crc = digital_skb_check_crc_f;
		break;

	default:
		break;
	}
}