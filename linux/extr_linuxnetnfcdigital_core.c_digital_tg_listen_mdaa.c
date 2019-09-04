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
struct digital_tg_mdaa_params {int /*<<< orphan*/  sc; int /*<<< orphan*/ * nfcid2; int /*<<< orphan*/  sel_res; int /*<<< orphan*/ * nfcid1; int /*<<< orphan*/  sens_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_TG_LISTEN_MDAA ; 
 int /*<<< orphan*/  DIGITAL_SEL_RES_NFC_DEP ; 
 int /*<<< orphan*/  DIGITAL_SENSF_FELICA_SC ; 
 int /*<<< orphan*/  DIGITAL_SENSF_NFCID2_NFC_DEP_B1 ; 
 int /*<<< orphan*/  DIGITAL_SENSF_NFCID2_NFC_DEP_B2 ; 
 int /*<<< orphan*/  DIGITAL_SENS_RES_NFC_DEP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFC_NFCID2_MAXSIZE ; 
 int digital_send_cmd (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct digital_tg_mdaa_params*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  digital_tg_recv_atr_req ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 struct digital_tg_mdaa_params* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digital_tg_listen_mdaa(struct nfc_digital_dev *ddev, u8 rf_tech)
{
	struct digital_tg_mdaa_params *params;

	params = kzalloc(sizeof(*params), GFP_KERNEL);
	if (!params)
		return -ENOMEM;

	params->sens_res = DIGITAL_SENS_RES_NFC_DEP;
	get_random_bytes(params->nfcid1, sizeof(params->nfcid1));
	params->sel_res = DIGITAL_SEL_RES_NFC_DEP;

	params->nfcid2[0] = DIGITAL_SENSF_NFCID2_NFC_DEP_B1;
	params->nfcid2[1] = DIGITAL_SENSF_NFCID2_NFC_DEP_B2;
	get_random_bytes(params->nfcid2 + 2, NFC_NFCID2_MAXSIZE - 2);
	params->sc = DIGITAL_SENSF_FELICA_SC;

	return digital_send_cmd(ddev, DIGITAL_CMD_TG_LISTEN_MDAA, NULL, params,
				500, digital_tg_recv_atr_req, NULL);
}