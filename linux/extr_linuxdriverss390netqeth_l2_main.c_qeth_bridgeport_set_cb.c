#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_6__ {int /*<<< orphan*/  return_code; } ;
struct TYPE_8__ {TYPE_2__ hdr; } ;
struct TYPE_7__ {TYPE_4__ sbp; } ;
struct TYPE_5__ {int /*<<< orphan*/  return_code; } ;
struct qeth_ipa_cmd {TYPE_3__ data; TYPE_1__ hdr; } ;
struct qeth_card {int dummy; } ;
struct _qeth_sbp_cbctl {int /*<<< orphan*/  cmd_rc; int /*<<< orphan*/  ipa_rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 

__attribute__((used)) static int qeth_bridgeport_set_cb(struct qeth_card *card,
	struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *)data;
	struct _qeth_sbp_cbctl *cbctl = (struct _qeth_sbp_cbctl *)reply->param;
	QETH_CARD_TEXT(card, 2, "brsetrcb");
	cbctl->ipa_rc = cmd->hdr.return_code;
	cbctl->cmd_rc = cmd->data.sbp.hdr.return_code;
	return 0;
}