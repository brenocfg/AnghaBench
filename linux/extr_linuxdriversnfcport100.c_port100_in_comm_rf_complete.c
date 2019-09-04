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
typedef  scalar_t__ u32 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct port100_cb_arg {int /*<<< orphan*/  complete_arg; int /*<<< orphan*/  (* complete_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ;} ;
struct port100 {int /*<<< orphan*/  nfc_digital_dev; TYPE_1__* interface; } ;
typedef  int /*<<< orphan*/  (* nfc_digital_cmd_complete_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 struct sk_buff* ERR_PTR (int) ; 
 int ETIMEDOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 scalar_t__ PORT100_CMD_STATUS_OK ; 
 scalar_t__ PORT100_CMD_STATUS_TIMEOUT ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct port100_cb_arg*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void port100_in_comm_rf_complete(struct port100 *dev, void *arg,
				       struct sk_buff *resp)
{
	struct port100_cb_arg *cb_arg = arg;
	nfc_digital_cmd_complete_t cb = cb_arg->complete_cb;
	u32 status;
	int rc;

	if (IS_ERR(resp)) {
		rc =  PTR_ERR(resp);
		goto exit;
	}

	if (resp->len < 4) {
		nfc_err(&dev->interface->dev,
			"Invalid packet length received\n");
		rc = -EIO;
		goto error;
	}

	status = le32_to_cpu(*(__le32 *)resp->data);

	skb_pull(resp, sizeof(u32));

	if (status == PORT100_CMD_STATUS_TIMEOUT) {
		rc = -ETIMEDOUT;
		goto error;
	}

	if (status != PORT100_CMD_STATUS_OK) {
		nfc_err(&dev->interface->dev,
			"in_comm_rf failed with status 0x%08x\n", status);
		rc = -EIO;
		goto error;
	}

	/* Remove collision bits byte */
	skb_pull(resp, 1);

	goto exit;

error:
	kfree_skb(resp);
	resp = ERR_PTR(rc);

exit:
	cb(dev->nfc_digital_dev, cb_arg->complete_arg, resp);

	kfree(cb_arg);
}