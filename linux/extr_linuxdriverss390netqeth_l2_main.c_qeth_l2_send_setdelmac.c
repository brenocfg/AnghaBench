#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  mac_length; } ;
struct TYPE_4__ {TYPE_1__ setdelmac; } ;
struct qeth_ipa_cmd {TYPE_2__ data; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_ipa_cmds { ____Placeholder_qeth_ipa_cmds } qeth_ipa_cmds ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 struct qeth_ipa_cmd* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qeth_cmd_buffer* qeth_get_ipacmd_buffer (struct qeth_card*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int qeth_setdelmac_makerc (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_send_setdelmac(struct qeth_card *card, __u8 *mac,
			   enum qeth_ipa_cmds ipacmd)
{
	struct qeth_ipa_cmd *cmd;
	struct qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "L2sdmac");
	iob = qeth_get_ipacmd_buffer(card, ipacmd, QETH_PROT_IPV4);
	if (!iob)
		return -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setdelmac.mac_length = ETH_ALEN;
	ether_addr_copy(cmd->data.setdelmac.mac, mac);
	return qeth_setdelmac_makerc(card, qeth_send_ipa_cmd(card, iob,
					   NULL, NULL));
}