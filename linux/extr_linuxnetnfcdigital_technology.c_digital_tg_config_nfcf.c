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
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_RF_TECH ; 
 int /*<<< orphan*/  NFC_DIGITAL_FRAMING_NFCF_NFC_DEP ; 
 int digital_tg_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digital_tg_config_nfcf(struct nfc_digital_dev *ddev, u8 rf_tech)
{
	int rc;

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH, rf_tech);
	if (rc)
		return rc;

	return digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				       NFC_DIGITAL_FRAMING_NFCF_NFC_DEP);
}