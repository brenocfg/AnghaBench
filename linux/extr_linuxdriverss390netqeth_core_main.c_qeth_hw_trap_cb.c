#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int dummy; } ;
struct TYPE_2__ {scalar_t__ return_code; } ;
struct qeth_ipa_cmd {TYPE_1__ hdr; } ;
struct qeth_card {int dummy; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,scalar_t__) ; 

__attribute__((used)) static int qeth_hw_trap_cb(struct qeth_card *card,
		struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd;
	__u16 rc;

	cmd = (struct qeth_ipa_cmd *)data;
	rc = cmd->hdr.return_code;
	if (rc)
		QETH_CARD_TEXT_(card, 2, "trapc:%x", rc);
	return 0;
}