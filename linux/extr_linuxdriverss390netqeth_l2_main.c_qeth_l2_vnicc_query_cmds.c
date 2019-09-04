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
typedef  int /*<<< orphan*/  u32 ;
struct qeth_card {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sup_cmds; } ;
struct TYPE_3__ {int /*<<< orphan*/  vnic_char; } ;
struct _qeth_l2_vnicc_request_cbctl {TYPE_2__ result; TYPE_1__ param; int /*<<< orphan*/  sub_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_VNICC_QUERY_CMDS ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_l2_vnicc_request (struct qeth_card*,struct _qeth_l2_vnicc_request_cbctl*) ; 

__attribute__((used)) static int qeth_l2_vnicc_query_cmds(struct qeth_card *card, u32 vnic_char,
				    u32 *sup_cmds)
{
	struct _qeth_l2_vnicc_request_cbctl cbctl;

	/* prepare callback control */
	cbctl.sub_cmd = IPA_VNICC_QUERY_CMDS;
	cbctl.param.vnic_char = vnic_char;
	cbctl.result.sup_cmds = sup_cmds;

	QETH_CARD_TEXT(card, 2, "vniccqcm");
	return qeth_l2_vnicc_request(card, &cbctl);
}