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
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct nfc_target {int dummy; } ;
struct nfc_digital_dev {scalar_t__ curr_nfc_dep_pni; int /*<<< orphan*/  target_fsc; } ;

/* Variables and functions */
 int DIGITAL_ATS_FSCI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIGITAL_ATS_MAX_FSC ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NFC_PROTO_ISO14443 ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/ * digital_ats_fsc ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_target_found (struct nfc_digital_dev*,struct nfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfc_target*) ; 

__attribute__((used)) static void digital_in_recv_ats(struct nfc_digital_dev *ddev, void *arg,
				struct sk_buff *resp)
{
	struct nfc_target *target = arg;
	u8 fsdi;
	int rc;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	if (resp->len < 2) {
		rc = -EIO;
		goto exit;
	}

	fsdi = DIGITAL_ATS_FSCI(resp->data[1]);
	if (fsdi >= 8)
		ddev->target_fsc = DIGITAL_ATS_MAX_FSC;
	else
		ddev->target_fsc = digital_ats_fsc[fsdi];

	ddev->curr_nfc_dep_pni = 0;

	rc = digital_target_found(ddev, target, NFC_PROTO_ISO14443);

exit:
	dev_kfree_skb(resp);
	kfree(target);

	if (rc)
		digital_poll_next_tech(ddev);
}