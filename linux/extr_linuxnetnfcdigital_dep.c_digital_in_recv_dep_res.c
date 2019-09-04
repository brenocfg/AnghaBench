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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct nfc_digital_dev {int (* skb_check_crc ) (struct sk_buff*) ;int local_payload_max; void* curr_nfc_dep_pni; struct sk_buff* saved_skb; struct sk_buff* chaining_skb; scalar_t__ nack_count; scalar_t__ atn_count; int /*<<< orphan*/  data_exch; } ;
struct digital_dep_req_res {scalar_t__ dir; scalar_t__ cmd; int /*<<< orphan*/  pfb; } ;
struct digital_data_exch {int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;

/* Variables and functions */
 scalar_t__ DIGITAL_CMD_DEP_RES ; 
 scalar_t__ DIGITAL_NFC_DEP_DID_BIT_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ DIGITAL_NFC_DEP_FRAME_DIR_IN ; 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_NACK_BIT_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ DIGITAL_NFC_DEP_NAD_BIT_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ DIGITAL_NFC_DEP_N_RETRY_ATN ; 
 scalar_t__ DIGITAL_NFC_DEP_N_RETRY_NACK ; 
#define  DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU 130 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_PFB_IS_TIMEOUT (int /*<<< orphan*/ ) ; 
#define  DIGITAL_NFC_DEP_PFB_I_PDU 129 
 void* DIGITAL_NFC_DEP_PFB_PNI (int /*<<< orphan*/ ) ; 
#define  DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU 128 
 int DIGITAL_NFC_DEP_PFB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_RTOX_MAX ; 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_RTOX_VALUE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int EMSGSIZE ; 
 int ETIMEDOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_in_send_ack ; 
 int digital_in_send_atn (struct nfc_digital_dev*,struct digital_data_exch*) ; 
 int digital_in_send_dep_req (struct nfc_digital_dev*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int digital_in_send_nack (struct nfc_digital_dev*,struct digital_data_exch*) ; 
 int digital_in_send_rtox (struct nfc_digital_dev*,struct digital_data_exch*,int /*<<< orphan*/ ) ; 
 int digital_in_send_saved_skb (struct nfc_digital_dev*,struct digital_data_exch*) ; 
 struct sk_buff* digital_recv_dep_data_gather (struct nfc_digital_dev*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,struct digital_data_exch*) ; 
 int digital_skb_pull_dep_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct digital_data_exch*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int stub1 (struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static void digital_in_recv_dep_res(struct nfc_digital_dev *ddev, void *arg,
				    struct sk_buff *resp)
{
	struct digital_data_exch *data_exch = arg;
	struct digital_dep_req_res *dep_res;
	u8 pfb;
	uint size;
	int rc;
	u8 rtox;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;

		if ((rc == -EIO || (rc == -ETIMEDOUT && ddev->nack_count)) &&
		    (ddev->nack_count++ < DIGITAL_NFC_DEP_N_RETRY_NACK)) {
			ddev->atn_count = 0;

			rc = digital_in_send_nack(ddev, data_exch);
			if (rc)
				goto error;

			return;
		} else if ((rc == -ETIMEDOUT) &&
			   (ddev->atn_count++ < DIGITAL_NFC_DEP_N_RETRY_ATN)) {
			ddev->nack_count = 0;

			rc = digital_in_send_atn(ddev, data_exch);
			if (rc)
				goto error;

			return;
		}

		goto exit;
	}

	rc = digital_skb_pull_dep_sod(ddev, resp);
	if (rc) {
		PROTOCOL_ERR("14.4.1.2");
		goto exit;
	}

	rc = ddev->skb_check_crc(resp);
	if (rc) {
		if ((resp->len >= 4) &&
		    (ddev->nack_count++ < DIGITAL_NFC_DEP_N_RETRY_NACK)) {
			ddev->atn_count = 0;

			rc = digital_in_send_nack(ddev, data_exch);
			if (rc)
				goto error;

			kfree_skb(resp);

			return;
		}

		PROTOCOL_ERR("14.4.1.6");
		goto error;
	}

	ddev->atn_count = 0;
	ddev->nack_count = 0;

	if (resp->len > ddev->local_payload_max) {
		rc = -EMSGSIZE;
		goto exit;
	}

	size = sizeof(struct digital_dep_req_res);
	dep_res = (struct digital_dep_req_res *)resp->data;

	if (resp->len < size || dep_res->dir != DIGITAL_NFC_DEP_FRAME_DIR_IN ||
	    dep_res->cmd != DIGITAL_CMD_DEP_RES) {
		rc = -EIO;
		goto error;
	}

	pfb = dep_res->pfb;

	if (DIGITAL_NFC_DEP_DID_BIT_SET(pfb)) {
		PROTOCOL_ERR("14.8.2.1");
		rc = -EIO;
		goto error;
	}

	if (DIGITAL_NFC_DEP_NAD_BIT_SET(pfb)) {
		rc = -EIO;
		goto exit;
	}

	if (size > resp->len) {
		rc = -EIO;
		goto error;
	}

	skb_pull(resp, size);

	switch (DIGITAL_NFC_DEP_PFB_TYPE(pfb)) {
	case DIGITAL_NFC_DEP_PFB_I_PDU:
		if (DIGITAL_NFC_DEP_PFB_PNI(pfb) != ddev->curr_nfc_dep_pni) {
			PROTOCOL_ERR("14.12.3.3");
			rc = -EIO;
			goto error;
		}

		ddev->curr_nfc_dep_pni =
			DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni + 1);

		kfree_skb(ddev->saved_skb);
		ddev->saved_skb = NULL;

		resp = digital_recv_dep_data_gather(ddev, pfb, resp,
						    digital_in_send_ack,
						    data_exch);
		if (IS_ERR(resp)) {
			rc = PTR_ERR(resp);
			resp = NULL;
			goto error;
		}

		/* If resp is NULL then we're still chaining so return and
		 * wait for the next part of the PDU.  Else, the PDU is
		 * complete so pass it up.
		 */
		if (!resp)
			return;

		rc = 0;
		break;

	case DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU:
		if (DIGITAL_NFC_DEP_NACK_BIT_SET(pfb)) {
			PROTOCOL_ERR("14.12.4.5");
			rc = -EIO;
			goto exit;
		}

		if (DIGITAL_NFC_DEP_PFB_PNI(pfb) != ddev->curr_nfc_dep_pni) {
			PROTOCOL_ERR("14.12.3.3");
			rc = -EIO;
			goto exit;
		}

		ddev->curr_nfc_dep_pni =
			DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni + 1);

		if (!ddev->chaining_skb) {
			PROTOCOL_ERR("14.12.4.3");
			rc = -EIO;
			goto exit;
		}

		/* The initiator has received a valid ACK. Free the last sent
		 * PDU and keep on sending chained skb.
		 */
		kfree_skb(ddev->saved_skb);
		ddev->saved_skb = NULL;

		rc = digital_in_send_dep_req(ddev, NULL,
					     ddev->chaining_skb,
					     ddev->data_exch);
		if (rc)
			goto error;

		goto free_resp;

	case DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU:
		if (!DIGITAL_NFC_DEP_PFB_IS_TIMEOUT(pfb)) { /* ATN */
			rc = digital_in_send_saved_skb(ddev, data_exch);
			if (rc)
				goto error;

			goto free_resp;
		}

		if (ddev->atn_count || ddev->nack_count) {
			PROTOCOL_ERR("14.12.4.4");
			rc = -EIO;
			goto error;
		}

		rtox = DIGITAL_NFC_DEP_RTOX_VALUE(resp->data[0]);
		if (!rtox || rtox > DIGITAL_NFC_DEP_RTOX_MAX) {
			PROTOCOL_ERR("14.8.4.1");
			rc = -EIO;
			goto error;
		}

		rc = digital_in_send_rtox(ddev, data_exch, rtox);
		if (rc)
			goto error;

		goto free_resp;
	}

exit:
	data_exch->cb(data_exch->cb_context, resp, rc);

error:
	kfree(data_exch);

	kfree_skb(ddev->chaining_skb);
	ddev->chaining_skb = NULL;

	kfree_skb(ddev->saved_skb);
	ddev->saved_skb = NULL;

	if (rc)
		kfree_skb(resp);

	return;

free_resp:
	dev_kfree_skb(resp);
}