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
struct trf7970a {int is_initiator; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NFC_DIGITAL_CONFIG_FRAMING 129 
#define  NFC_DIGITAL_CONFIG_RF_TECH 128 
 scalar_t__ TRF7970A_ST_PWR_OFF ; 
 scalar_t__ TRF7970A_ST_RF_OFF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct trf7970a* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int trf7970a_in_config_framing (struct trf7970a*,int) ; 
 int trf7970a_in_config_rf_tech (struct trf7970a*,int) ; 
 int trf7970a_switch_rf_on (struct trf7970a*) ; 

__attribute__((used)) static int trf7970a_in_configure_hw(struct nfc_digital_dev *ddev, int type,
				    int param)
{
	struct trf7970a *trf = nfc_digital_get_drvdata(ddev);
	int ret;

	dev_dbg(trf->dev, "Configure hw - type: %d, param: %d\n", type, param);

	mutex_lock(&trf->lock);

	trf->is_initiator = true;

	if ((trf->state == TRF7970A_ST_PWR_OFF) ||
	    (trf->state == TRF7970A_ST_RF_OFF)) {
		ret = trf7970a_switch_rf_on(trf);
		if (ret)
			goto err_unlock;
	}

	switch (type) {
	case NFC_DIGITAL_CONFIG_RF_TECH:
		ret = trf7970a_in_config_rf_tech(trf, param);
		break;
	case NFC_DIGITAL_CONFIG_FRAMING:
		ret = trf7970a_in_config_framing(trf, param);
		break;
	default:
		dev_dbg(trf->dev, "Unknown type: %d\n", type);
		ret = -EINVAL;
	}

err_unlock:
	mutex_unlock(&trf->lock);
	return ret;
}