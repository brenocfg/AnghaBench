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
struct sk_buff {int len; scalar_t__* data; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIGITAL_CMD_SENSF_REQ ; 
 int /*<<< orphan*/  IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_tg_recv_atr_req (struct nfc_digital_dev*,void*,struct sk_buff*) ; 
 int /*<<< orphan*/  digital_tg_recv_sensf_req (struct nfc_digital_dev*,void*,struct sk_buff*) ; 

__attribute__((used)) static void digital_tg_recv_atr_or_sensf_req(struct nfc_digital_dev *ddev,
		void *arg, struct sk_buff *resp)
{
	if (!IS_ERR(resp) && (resp->len >= 2) &&
			(resp->data[1] == DIGITAL_CMD_SENSF_REQ))
		digital_tg_recv_sensf_req(ddev, arg, resp);
	else
		digital_tg_recv_atr_req(ddev, arg, resp);

	return;
}