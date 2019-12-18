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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;
typedef  int /*<<< orphan*/  nfc_digital_cmd_complete_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_TG_SEND ; 
 int digital_send_cmd (struct nfc_digital_dev*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline int digital_tg_send_cmd(struct nfc_digital_dev *ddev,
			struct sk_buff *skb, u16 timeout,
			nfc_digital_cmd_complete_t cmd_cb, void *cb_context)
{
	return digital_send_cmd(ddev, DIGITAL_CMD_TG_SEND, skb, NULL, timeout,
				cmd_cb, cb_context);
}