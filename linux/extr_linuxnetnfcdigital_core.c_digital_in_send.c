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
struct nfc_target {int dummy; } ;
struct nfc_digital_dev {scalar_t__ curr_protocol; int /*<<< orphan*/  (* skb_add_crc ) (struct sk_buff*) ;} ;
struct nfc_dev {int dummy; } ;
struct digital_data_exch {void* cb_context; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  data_exchange_cb_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NFC_PROTO_ISO14443 ; 
 scalar_t__ NFC_PROTO_ISO14443_B ; 
 scalar_t__ NFC_PROTO_NFC_DEP ; 
 int digital_in_iso_dep_push_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int digital_in_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,struct digital_data_exch*) ; 
 int /*<<< orphan*/  digital_in_send_complete ; 
 int digital_in_send_dep_req (struct nfc_digital_dev*,struct nfc_target*,struct sk_buff*,struct digital_data_exch*) ; 
 int /*<<< orphan*/  kfree (struct digital_data_exch*) ; 
 struct digital_data_exch* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static int digital_in_send(struct nfc_dev *nfc_dev, struct nfc_target *target,
			   struct sk_buff *skb, data_exchange_cb_t cb,
			   void *cb_context)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);
	struct digital_data_exch *data_exch;
	int rc;

	data_exch = kzalloc(sizeof(*data_exch), GFP_KERNEL);
	if (!data_exch)
		return -ENOMEM;

	data_exch->cb = cb;
	data_exch->cb_context = cb_context;

	if (ddev->curr_protocol == NFC_PROTO_NFC_DEP) {
		rc = digital_in_send_dep_req(ddev, target, skb, data_exch);
		goto exit;
	}

	if ((ddev->curr_protocol == NFC_PROTO_ISO14443) ||
	    (ddev->curr_protocol == NFC_PROTO_ISO14443_B)) {
		rc = digital_in_iso_dep_push_sod(ddev, skb);
		if (rc)
			goto exit;
	}

	ddev->skb_add_crc(skb);

	rc = digital_in_send_cmd(ddev, skb, 500, digital_in_send_complete,
				 data_exch);

exit:
	if (rc)
		kfree(data_exch);

	return rc;
}