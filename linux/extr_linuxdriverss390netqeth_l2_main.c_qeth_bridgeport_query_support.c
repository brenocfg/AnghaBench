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
struct qeth_sbp_query_cmds_supp {int dummy; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  supported_funcs; int /*<<< orphan*/  role; } ;
struct TYPE_6__ {TYPE_2__ sbp; } ;
struct qeth_card {TYPE_3__ options; } ;
struct TYPE_4__ {int /*<<< orphan*/  supported; } ;
struct _qeth_sbp_cbctl {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_SBP_QUERY_COMMANDS_SUPPORTED ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_SBP_ROLE_NONE ; 
 scalar_t__ qeth_bridgeport_makerc (struct qeth_card*,struct _qeth_sbp_cbctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_bridgeport_query_support_cb ; 
 struct qeth_cmd_buffer* qeth_sbp_build_cmd (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void qeth_bridgeport_query_support(struct qeth_card *card)
{
	struct qeth_cmd_buffer *iob;
	struct _qeth_sbp_cbctl cbctl;

	QETH_CARD_TEXT(card, 2, "brqsuppo");
	iob = qeth_sbp_build_cmd(card, IPA_SBP_QUERY_COMMANDS_SUPPORTED,
				 sizeof(struct qeth_sbp_query_cmds_supp));
	if (!iob)
		return;
	if (qeth_send_ipa_cmd(card, iob, qeth_bridgeport_query_support_cb,
							(void *)&cbctl) ||
	    qeth_bridgeport_makerc(card, &cbctl,
					IPA_SBP_QUERY_COMMANDS_SUPPORTED)) {
		/* non-zero makerc signifies failure, and produce messages */
		card->options.sbp.role = QETH_SBP_ROLE_NONE;
		return;
	}
	card->options.sbp.supported_funcs = cbctl.data.supported;
}