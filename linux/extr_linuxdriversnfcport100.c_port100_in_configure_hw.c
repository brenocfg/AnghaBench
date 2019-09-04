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
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NFC_DIGITAL_CONFIG_FRAMING ; 
 int NFC_DIGITAL_CONFIG_RF_TECH ; 
 int port100_in_set_framing (struct nfc_digital_dev*,int) ; 
 int port100_in_set_rf (struct nfc_digital_dev*,int) ; 

__attribute__((used)) static int port100_in_configure_hw(struct nfc_digital_dev *ddev, int type,
				   int param)
{
	if (type == NFC_DIGITAL_CONFIG_RF_TECH)
		return port100_in_set_rf(ddev, param);

	if (type == NFC_DIGITAL_CONFIG_FRAMING)
		return port100_in_set_framing(ddev, param);

	return -EINVAL;
}