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
struct qeth_ipacmd_setadpparms {int dummy; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPA_SETADP_QUERY_COMMANDS_SUPPORTED ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 struct qeth_cmd_buffer* qeth_get_adapter_cmd (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qeth_query_setadapterparms_cb ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_query_setadapterparms(struct qeth_card *card)
{
	int rc;
	struct qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 3, "queryadp");
	iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_COMMANDS_SUPPORTED,
				   sizeof(struct qeth_ipacmd_setadpparms));
	if (!iob)
		return -ENOMEM;
	rc = qeth_send_ipa_cmd(card, iob, qeth_query_setadapterparms_cb, NULL);
	return rc;
}