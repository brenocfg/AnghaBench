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
typedef  int /*<<< orphan*/  u16 ;
struct trf7970a {int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
struct nfc_digital_dev {int dummy; } ;
typedef  int /*<<< orphan*/  nfc_digital_cmd_complete_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_RF_TECH ; 
 int /*<<< orphan*/  NFC_DIGITAL_FRAMING_NFCA_NFC_DEP ; 
 int /*<<< orphan*/  NFC_DIGITAL_RF_TECH_106A ; 
 int _trf7970a_tg_listen (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trf7970a* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int trf7970a_tg_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trf7970a_tg_listen_md(struct nfc_digital_dev *ddev,
				 u16 timeout, nfc_digital_cmd_complete_t cb,
				 void *arg)
{
	struct trf7970a *trf = nfc_digital_get_drvdata(ddev);
	int ret;

	dev_dbg(trf->dev, "Listen MD - state: %d, timeout: %d ms\n",
		trf->state, timeout);

	ret = trf7970a_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				       NFC_DIGITAL_RF_TECH_106A);
	if (ret)
		return ret;

	ret = trf7970a_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				       NFC_DIGITAL_FRAMING_NFCA_NFC_DEP);
	if (ret)
		return ret;

	return _trf7970a_tg_listen(ddev, timeout, cb, arg, true);
}