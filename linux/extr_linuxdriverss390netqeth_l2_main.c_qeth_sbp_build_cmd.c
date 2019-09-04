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
struct qeth_ipacmd_sbp_hdr {int dummy; } ;
struct TYPE_5__ {int cmdlength; int command_code; int used_total; int seq_no; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
struct TYPE_7__ {TYPE_2__ sbp; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct qeth_card {TYPE_4__ info; } ;
typedef  enum qeth_ipa_sbp_cmd { ____Placeholder_qeth_ipa_sbp_cmd } qeth_ipa_sbp_cmd ;
typedef  enum qeth_ipa_cmds { ____Placeholder_qeth_ipa_cmds } qeth_ipa_cmds ;

/* Variables and functions */
 int IPA_CMD_SETBRIDGEPORT_IQD ; 
 int IPA_CMD_SETBRIDGEPORT_OSA ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 struct qeth_ipa_cmd* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 struct qeth_cmd_buffer* qeth_get_ipacmd_buffer (struct qeth_card*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qeth_cmd_buffer *qeth_sbp_build_cmd(struct qeth_card *card,
						  enum qeth_ipa_sbp_cmd sbp_cmd,
						  unsigned int cmd_length)
{
	enum qeth_ipa_cmds ipa_cmd = (card->info.type == QETH_CARD_TYPE_IQD) ?
					IPA_CMD_SETBRIDGEPORT_IQD :
					IPA_CMD_SETBRIDGEPORT_OSA;
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd *cmd;

	iob = qeth_get_ipacmd_buffer(card, ipa_cmd, 0);
	if (!iob)
		return iob;
	cmd = __ipa_cmd(iob);
	cmd->data.sbp.hdr.cmdlength = sizeof(struct qeth_ipacmd_sbp_hdr) +
				      cmd_length;
	cmd->data.sbp.hdr.command_code = sbp_cmd;
	cmd->data.sbp.hdr.used_total = 1;
	cmd->data.sbp.hdr.seq_no = 1;
	return iob;
}