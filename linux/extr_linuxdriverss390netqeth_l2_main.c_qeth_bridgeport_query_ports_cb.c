#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct qeth_sbp_query_ports {int entry_length; scalar_t__ num_entries; TYPE_8__* entry; } ;
struct qeth_sbp_port_entry {int dummy; } ;
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_11__ {int return_code; } ;
struct TYPE_9__ {struct qeth_sbp_query_ports query_ports; } ;
struct TYPE_12__ {TYPE_3__ hdr; TYPE_1__ data; } ;
struct TYPE_13__ {TYPE_4__ sbp; } ;
struct TYPE_10__ {scalar_t__ return_code; } ;
struct qeth_ipa_cmd {TYPE_5__ data; TYPE_2__ hdr; } ;
struct qeth_card {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/ * state; int /*<<< orphan*/ * role; } ;
struct TYPE_15__ {TYPE_6__ qports; } ;
struct _qeth_sbp_cbctl {scalar_t__ ipa_rc; int cmd_rc; TYPE_7__ data; } ;
struct TYPE_16__ {int /*<<< orphan*/  state; int /*<<< orphan*/  role; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 

__attribute__((used)) static int qeth_bridgeport_query_ports_cb(struct qeth_card *card,
	struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct qeth_sbp_query_ports *qports = &cmd->data.sbp.data.query_ports;
	struct _qeth_sbp_cbctl *cbctl = (struct _qeth_sbp_cbctl *)reply->param;

	QETH_CARD_TEXT(card, 2, "brqprtcb");
	cbctl->ipa_rc = cmd->hdr.return_code;
	cbctl->cmd_rc = cmd->data.sbp.hdr.return_code;
	if ((cbctl->ipa_rc != 0) || (cbctl->cmd_rc != 0))
		return 0;
	if (qports->entry_length != sizeof(struct qeth_sbp_port_entry)) {
		cbctl->cmd_rc = 0xffff;
		QETH_CARD_TEXT_(card, 2, "SBPs%04x", qports->entry_length);
		return 0;
	}
	/* first entry contains the state of the local port */
	if (qports->num_entries > 0) {
		if (cbctl->data.qports.role)
			*cbctl->data.qports.role = qports->entry[0].role;
		if (cbctl->data.qports.state)
			*cbctl->data.qports.state = qports->entry[0].state;
	}
	return 0;
}