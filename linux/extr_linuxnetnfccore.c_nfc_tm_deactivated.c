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
struct nfc_dev {int dep_link_up; int /*<<< orphan*/  rf_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_RF_NONE ; 
 int nfc_genl_tm_deactivated (struct nfc_dev*) ; 

int nfc_tm_deactivated(struct nfc_dev *dev)
{
	dev->dep_link_up = false;
	dev->rf_mode = NFC_RF_NONE;

	return nfc_genl_tm_deactivated(dev);
}