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
typedef  void* u32 ;
struct qeth_card {int dummy; } ;
struct TYPE_2__ {void* vnic_char; } ;
struct _qeth_l2_vnicc_request_cbctl {TYPE_1__ param; void* sub_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_l2_vnicc_request (struct qeth_card*,struct _qeth_l2_vnicc_request_cbctl*) ; 

__attribute__((used)) static int qeth_l2_vnicc_set_char(struct qeth_card *card, u32 vnic_char,
				      u32 cmd)
{
	struct _qeth_l2_vnicc_request_cbctl cbctl;

	/* prepare callback control */
	cbctl.sub_cmd = cmd;
	cbctl.param.vnic_char = vnic_char;

	QETH_CARD_TEXT(card, 2, "vniccedc");
	return qeth_l2_vnicc_request(card, &cbctl);
}