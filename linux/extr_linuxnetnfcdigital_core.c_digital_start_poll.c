#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nfc_digital_dev {int protocols; int /*<<< orphan*/  poll_work; scalar_t__ poll_tech_count; TYPE_1__* ops; scalar_t__ poll_tech_index; scalar_t__ curr_protocol; } ;
struct nfc_dev {int dummy; } ;
typedef  int __u32 ;
struct TYPE_2__ {scalar_t__ tg_listen_md; scalar_t__ tg_listen_mdaa; } ;

/* Variables and functions */
 int DIGITAL_PROTO_ISO15693_RF_TECH ; 
 int DIGITAL_PROTO_NFCA_RF_TECH ; 
 int DIGITAL_PROTO_NFCB_RF_TECH ; 
 int DIGITAL_PROTO_NFCF_RF_TECH ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  NFC_DIGITAL_RF_TECH_106A ; 
 int /*<<< orphan*/  NFC_DIGITAL_RF_TECH_106B ; 
 int /*<<< orphan*/  NFC_DIGITAL_RF_TECH_212F ; 
 int /*<<< orphan*/  NFC_DIGITAL_RF_TECH_424F ; 
 int /*<<< orphan*/  NFC_DIGITAL_RF_TECH_ISO15693 ; 
 int NFC_PROTO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  digital_add_poll_tech (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digital_in_send_iso15693_inv_req ; 
 int /*<<< orphan*/  digital_in_send_sens_req ; 
 int /*<<< orphan*/  digital_in_send_sensb_req ; 
 int /*<<< orphan*/  digital_in_send_sensf_req ; 
 int /*<<< orphan*/  digital_tg_listen_md ; 
 int /*<<< orphan*/  digital_tg_listen_mdaa ; 
 int /*<<< orphan*/  digital_tg_listen_nfca ; 
 int /*<<< orphan*/  digital_tg_listen_nfcf ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digital_start_poll(struct nfc_dev *nfc_dev, __u32 im_protocols,
			      __u32 tm_protocols)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);
	u32 matching_im_protocols, matching_tm_protocols;

	pr_debug("protocols: im 0x%x, tm 0x%x, supported 0x%x\n", im_protocols,
		 tm_protocols, ddev->protocols);

	matching_im_protocols = ddev->protocols & im_protocols;
	matching_tm_protocols = ddev->protocols & tm_protocols;

	if (!matching_im_protocols && !matching_tm_protocols) {
		pr_err("Unknown protocol\n");
		return -EINVAL;
	}

	if (ddev->poll_tech_count) {
		pr_err("Already polling\n");
		return -EBUSY;
	}

	if (ddev->curr_protocol) {
		pr_err("A target is already active\n");
		return -EBUSY;
	}

	ddev->poll_tech_count = 0;
	ddev->poll_tech_index = 0;

	if (matching_im_protocols & DIGITAL_PROTO_NFCA_RF_TECH)
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_106A,
				      digital_in_send_sens_req);

	if (matching_im_protocols & DIGITAL_PROTO_NFCB_RF_TECH)
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_106B,
				      digital_in_send_sensb_req);

	if (matching_im_protocols & DIGITAL_PROTO_NFCF_RF_TECH) {
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_212F,
				      digital_in_send_sensf_req);

		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_424F,
				      digital_in_send_sensf_req);
	}

	if (matching_im_protocols & DIGITAL_PROTO_ISO15693_RF_TECH)
		digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_ISO15693,
				      digital_in_send_iso15693_inv_req);

	if (matching_tm_protocols & NFC_PROTO_NFC_DEP_MASK) {
		if (ddev->ops->tg_listen_mdaa) {
			digital_add_poll_tech(ddev, 0,
					      digital_tg_listen_mdaa);
		} else if (ddev->ops->tg_listen_md) {
			digital_add_poll_tech(ddev, 0,
					      digital_tg_listen_md);
		} else {
			digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_106A,
					      digital_tg_listen_nfca);

			digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_212F,
					      digital_tg_listen_nfcf);

			digital_add_poll_tech(ddev, NFC_DIGITAL_RF_TECH_424F,
					      digital_tg_listen_nfcf);
		}
	}

	if (!ddev->poll_tech_count) {
		pr_err("Unsupported protocols: im=0x%x, tm=0x%x\n",
		       matching_im_protocols, matching_tm_protocols);
		return -EINVAL;
	}

	schedule_delayed_work(&ddev->poll_work, 0);

	return 0;
}