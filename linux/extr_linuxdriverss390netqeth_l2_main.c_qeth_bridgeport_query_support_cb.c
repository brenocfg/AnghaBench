#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_10__ {scalar_t__ supported_cmds; } ;
struct TYPE_11__ {TYPE_3__ query_cmds_supp; } ;
struct TYPE_9__ {scalar_t__ return_code; } ;
struct TYPE_12__ {TYPE_4__ data; TYPE_2__ hdr; } ;
struct TYPE_13__ {TYPE_5__ sbp; } ;
struct TYPE_8__ {scalar_t__ return_code; } ;
struct qeth_ipa_cmd {TYPE_6__ data; TYPE_1__ hdr; } ;
struct qeth_card {int dummy; } ;
struct TYPE_14__ {scalar_t__ supported; } ;
struct _qeth_sbp_cbctl {scalar_t__ ipa_rc; scalar_t__ cmd_rc; TYPE_7__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 

__attribute__((used)) static int qeth_bridgeport_query_support_cb(struct qeth_card *card,
	struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct _qeth_sbp_cbctl *cbctl = (struct _qeth_sbp_cbctl *)reply->param;
	QETH_CARD_TEXT(card, 2, "brqsupcb");
	cbctl->ipa_rc = cmd->hdr.return_code;
	cbctl->cmd_rc = cmd->data.sbp.hdr.return_code;
	if ((cbctl->ipa_rc == 0) && (cbctl->cmd_rc == 0)) {
		cbctl->data.supported =
			cmd->data.sbp.data.query_cmds_supp.supported_cmds;
	} else {
		cbctl->data.supported = 0;
	}
	return 0;
}