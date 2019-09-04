#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ atr_req; scalar_t__ atr_req_len; } ;
struct TYPE_4__ {scalar_t__ atr_res; scalar_t__ atr_res_len; } ;
struct TYPE_6__ {TYPE_2__ listen_nfc_dep; TYPE_1__ poll_nfc_dep; } ;
struct nci_rf_intf_activated_ntf {scalar_t__ activation_params_len; int activation_rf_tech_and_mode; TYPE_3__ activation_params; } ;
struct nci_dev {void* remote_gb_len; int /*<<< orphan*/  remote_gb; } ;

/* Variables and functions */
#define  NCI_NFC_A_PASSIVE_LISTEN_MODE 131 
#define  NCI_NFC_A_PASSIVE_POLL_MODE 130 
#define  NCI_NFC_F_PASSIVE_LISTEN_MODE 129 
#define  NCI_NFC_F_PASSIVE_POLL_MODE 128 
 int NCI_STATUS_OK ; 
 int NCI_STATUS_RF_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  NFC_ATR_REQ_GB_MAXSIZE ; 
 scalar_t__ NFC_ATR_REQ_GT_OFFSET ; 
 int /*<<< orphan*/  NFC_ATR_RES_GB_MAXSIZE ; 
 scalar_t__ NFC_ATR_RES_GT_OFFSET ; 
 int /*<<< orphan*/  __u8 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,void*) ; 
 void* min_t (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int nci_store_general_bytes_nfc_dep(struct nci_dev *ndev,
		struct nci_rf_intf_activated_ntf *ntf)
{
	ndev->remote_gb_len = 0;

	if (ntf->activation_params_len <= 0)
		return NCI_STATUS_OK;

	switch (ntf->activation_rf_tech_and_mode) {
	case NCI_NFC_A_PASSIVE_POLL_MODE:
	case NCI_NFC_F_PASSIVE_POLL_MODE:
		ndev->remote_gb_len = min_t(__u8,
			(ntf->activation_params.poll_nfc_dep.atr_res_len
						- NFC_ATR_RES_GT_OFFSET),
			NFC_ATR_RES_GB_MAXSIZE);
		memcpy(ndev->remote_gb,
		       (ntf->activation_params.poll_nfc_dep.atr_res
						+ NFC_ATR_RES_GT_OFFSET),
		       ndev->remote_gb_len);
		break;

	case NCI_NFC_A_PASSIVE_LISTEN_MODE:
	case NCI_NFC_F_PASSIVE_LISTEN_MODE:
		ndev->remote_gb_len = min_t(__u8,
			(ntf->activation_params.listen_nfc_dep.atr_req_len
						- NFC_ATR_REQ_GT_OFFSET),
			NFC_ATR_REQ_GB_MAXSIZE);
		memcpy(ndev->remote_gb,
		       (ntf->activation_params.listen_nfc_dep.atr_req
						+ NFC_ATR_REQ_GT_OFFSET),
		       ndev->remote_gb_len);
		break;

	default:
		pr_err("unsupported activation_rf_tech_and_mode 0x%x\n",
		       ntf->activation_rf_tech_and_mode);
		return NCI_STATUS_RF_PROTOCOL_ERROR;
	}

	return NCI_STATUS_OK;
}