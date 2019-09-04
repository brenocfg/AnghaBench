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
struct sk_buff {int dummy; } ;
struct nfc_digital_dev {scalar_t__ curr_protocol; int (* skb_check_crc ) (struct sk_buff*) ;} ;
struct digital_data_exch {int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 scalar_t__ NFC_PROTO_ISO14443 ; 
 scalar_t__ NFC_PROTO_ISO14443_B ; 
 scalar_t__ NFC_PROTO_MIFARE ; 
 int PTR_ERR (struct sk_buff*) ; 
 int digital_in_iso_dep_pull_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int digital_in_recv_mifare_res (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct digital_data_exch*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static void digital_in_send_complete(struct nfc_digital_dev *ddev, void *arg,
				     struct sk_buff *resp)
{
	struct digital_data_exch *data_exch = arg;
	int rc;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto done;
	}

	if (ddev->curr_protocol == NFC_PROTO_MIFARE) {
		rc = digital_in_recv_mifare_res(resp);
		/* crc check is done in digital_in_recv_mifare_res() */
		goto done;
	}

	if ((ddev->curr_protocol == NFC_PROTO_ISO14443) ||
	    (ddev->curr_protocol == NFC_PROTO_ISO14443_B)) {
		rc = digital_in_iso_dep_pull_sod(ddev, resp);
		if (rc)
			goto done;
	}

	rc = ddev->skb_check_crc(resp);

done:
	if (rc) {
		kfree_skb(resp);
		resp = NULL;
	}

	data_exch->cb(data_exch->cb_context, resp, rc);

	kfree(data_exch);
}