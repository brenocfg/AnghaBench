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
struct pn533 {int /*<<< orphan*/  dev; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN533_CFGITEM_RF_FIELD ; 
 int PN533_CFGITEM_RF_FIELD_AUTO_RFCA ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ ,char*) ; 
 struct pn533* nfc_get_drvdata (struct nfc_dev*) ; 
 int pn533_set_configuration (struct pn533*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int pn533_rf_field(struct nfc_dev *nfc_dev, u8 rf)
{
	struct pn533 *dev = nfc_get_drvdata(nfc_dev);
	u8 rf_field = !!rf;
	int rc;

	rf_field |= PN533_CFGITEM_RF_FIELD_AUTO_RFCA;

	rc = pn533_set_configuration(dev, PN533_CFGITEM_RF_FIELD,
				     (u8 *)&rf_field, 1);
	if (rc) {
		nfc_err(dev->dev, "Error on setting RF field\n");
		return rc;
	}

	return rc;
}