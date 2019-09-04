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
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  IPA_CMD_LENGTH ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  qeth_clear_ipacmd_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_prepare_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int qeth_send_control_data (struct qeth_card*,int /*<<< orphan*/ ,struct qeth_cmd_buffer*,int (*) (struct qeth_card*,struct qeth_reply*,unsigned long),void*) ; 

int qeth_send_ipa_cmd(struct qeth_card *card, struct qeth_cmd_buffer *iob,
		int (*reply_cb)(struct qeth_card *, struct qeth_reply*,
			unsigned long),
		void *reply_param)
{
	int rc;

	QETH_CARD_TEXT(card, 4, "sendipa");
	qeth_prepare_ipa_cmd(card, iob);
	rc = qeth_send_control_data(card, IPA_CMD_LENGTH,
						iob, reply_cb, reply_param);
	if (rc == -ETIME) {
		qeth_clear_ipacmd_list(card);
		qeth_schedule_recovery(card);
	}
	return rc;
}