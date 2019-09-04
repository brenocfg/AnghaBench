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
struct TYPE_6__ {scalar_t__ flags_32bit; } ;
struct TYPE_4__ {TYPE_3__ data; } ;
struct TYPE_5__ {TYPE_1__ setassparms; } ;
struct qeth_ipa_cmd {TYPE_2__ data; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;
typedef  scalar_t__ __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 struct qeth_ipa_cmd* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,void*,int) ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int (*) (struct qeth_card*,struct qeth_reply*,unsigned long),void*) ; 

int qeth_send_setassparms(struct qeth_card *card,
			  struct qeth_cmd_buffer *iob, __u16 len, long data,
			  int (*reply_cb)(struct qeth_card *,
					  struct qeth_reply *, unsigned long),
			  void *reply_param)
{
	int rc;
	struct qeth_ipa_cmd *cmd;

	QETH_CARD_TEXT(card, 4, "sendassp");

	cmd = __ipa_cmd(iob);
	if (len <= sizeof(__u32))
		cmd->data.setassparms.data.flags_32bit = (__u32) data;
	else   /* (len > sizeof(__u32)) */
		memcpy(&cmd->data.setassparms.data, (void *) data, len);

	rc = qeth_send_ipa_cmd(card, iob, reply_cb, reply_param);
	return rc;
}