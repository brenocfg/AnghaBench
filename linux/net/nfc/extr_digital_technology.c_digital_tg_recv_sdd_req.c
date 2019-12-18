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
typedef  scalar_t__ u8 ;
struct sk_buff {int len; scalar_t__* data; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIGITAL_CMD_SEL_REQ_CL1 ; 
 scalar_t__ DIGITAL_SDD_REQ_SEL_PAR ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_tg_send_sdd_res (struct nfc_digital_dev*) ; 

__attribute__((used)) static void digital_tg_recv_sdd_req(struct nfc_digital_dev *ddev, void *arg,
				    struct sk_buff *resp)
{
	u8 *sdd_req;
	int rc;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	sdd_req = resp->data;

	if (resp->len < 2 || sdd_req[0] != DIGITAL_CMD_SEL_REQ_CL1 ||
	    sdd_req[1] != DIGITAL_SDD_REQ_SEL_PAR) {
		rc = -EINVAL;
		goto exit;
	}

	rc = digital_tg_send_sdd_res(ddev);

exit:
	if (rc)
		digital_poll_next_tech(ddev);

	dev_kfree_skb(resp);
}