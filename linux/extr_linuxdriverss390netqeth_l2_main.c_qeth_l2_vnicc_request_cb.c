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
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_16__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_14__ {int /*<<< orphan*/  sup_cmds; } ;
struct TYPE_13__ {int /*<<< orphan*/  cur; int /*<<< orphan*/  sup; } ;
struct qeth_ipacmd_vnicc {TYPE_8__ getset_timeout; TYPE_6__ query_cmds; TYPE_5__ hdr; } ;
struct TYPE_10__ {scalar_t__ return_code; } ;
struct TYPE_9__ {struct qeth_ipacmd_vnicc vnicc; } ;
struct qeth_ipa_cmd {TYPE_2__ hdr; TYPE_1__ data; } ;
struct TYPE_11__ {int /*<<< orphan*/  cur_chars; int /*<<< orphan*/  sup_chars; } ;
struct TYPE_12__ {TYPE_3__ vnicc; } ;
struct qeth_card {TYPE_4__ options; } ;
struct TYPE_15__ {int /*<<< orphan*/ * timeout; int /*<<< orphan*/ * sup_cmds; } ;
struct _qeth_l2_vnicc_request_cbctl {scalar_t__ sub_cmd; TYPE_7__ result; } ;

/* Variables and functions */
 scalar_t__ IPA_VNICC_GET_TIMEOUT ; 
 scalar_t__ IPA_VNICC_QUERY_CMDS ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 

__attribute__((used)) static int qeth_l2_vnicc_request_cb(struct qeth_card *card,
				    struct qeth_reply *reply,
				    unsigned long data)
{
	struct _qeth_l2_vnicc_request_cbctl *cbctl =
		(struct _qeth_l2_vnicc_request_cbctl *) reply->param;
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct qeth_ipacmd_vnicc *rep = &cmd->data.vnicc;

	QETH_CARD_TEXT(card, 2, "vniccrcb");
	if (cmd->hdr.return_code)
		return 0;
	/* return results to caller */
	card->options.vnicc.sup_chars = rep->hdr.sup;
	card->options.vnicc.cur_chars = rep->hdr.cur;

	if (cbctl->sub_cmd == IPA_VNICC_QUERY_CMDS)
		*cbctl->result.sup_cmds = rep->query_cmds.sup_cmds;

	if (cbctl->sub_cmd == IPA_VNICC_GET_TIMEOUT)
		*cbctl->result.timeout = rep->getset_timeout.timeout;

	return 0;
}