#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_7__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  supported; } ;
struct TYPE_8__ {TYPE_2__ chksum; } ;
struct TYPE_6__ {scalar_t__ command_code; } ;
struct TYPE_9__ {TYPE_3__ data; TYPE_1__ hdr; } ;
struct TYPE_10__ {TYPE_4__ setassparms; } ;
struct qeth_ipa_cmd {TYPE_5__ data; } ;
struct qeth_checksum_cmd {int /*<<< orphan*/  enabled; int /*<<< orphan*/  supported; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPA_CMD_ASS_ENABLE ; 
 scalar_t__ IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qeth_checksum_cmd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qeth_setassparms_inspect_rc (struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_ipa_checksum_run_cmd_cb(struct qeth_card *card,
					struct qeth_reply *reply,
					unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct qeth_checksum_cmd *chksum_cb =
				(struct qeth_checksum_cmd *)reply->param;

	QETH_CARD_TEXT(card, 4, "chkdoccb");
	if (qeth_setassparms_inspect_rc(cmd))
		return 0;

	memset(chksum_cb, 0, sizeof(*chksum_cb));
	if (cmd->data.setassparms.hdr.command_code == IPA_CMD_ASS_START) {
		chksum_cb->supported =
				cmd->data.setassparms.data.chksum.supported;
		QETH_CARD_TEXT_(card, 3, "strt:%x", chksum_cb->supported);
	}
	if (cmd->data.setassparms.hdr.command_code == IPA_CMD_ASS_ENABLE) {
		chksum_cb->supported =
				cmd->data.setassparms.data.chksum.supported;
		chksum_cb->enabled =
				cmd->data.setassparms.data.chksum.enabled;
		QETH_CARD_TEXT_(card, 3, "supp:%x", chksum_cb->supported);
		QETH_CARD_TEXT_(card, 3, "enab:%x", chksum_cb->enabled);
	}
	return 0;
}