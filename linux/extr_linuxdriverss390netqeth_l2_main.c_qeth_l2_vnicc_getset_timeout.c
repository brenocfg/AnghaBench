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
typedef  scalar_t__ u32 ;
struct qeth_card {int dummy; } ;
struct TYPE_4__ {scalar_t__* timeout; } ;
struct TYPE_3__ {scalar_t__ timeout; scalar_t__ vnic_char; } ;
struct _qeth_l2_vnicc_request_cbctl {TYPE_2__ result; TYPE_1__ param; scalar_t__ sub_cmd; } ;

/* Variables and functions */
 scalar_t__ IPA_VNICC_GET_TIMEOUT ; 
 scalar_t__ IPA_VNICC_SET_TIMEOUT ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_l2_vnicc_request (struct qeth_card*,struct _qeth_l2_vnicc_request_cbctl*) ; 

__attribute__((used)) static int qeth_l2_vnicc_getset_timeout(struct qeth_card *card, u32 vnicc,
					u32 cmd, u32 *timeout)
{
	struct _qeth_l2_vnicc_request_cbctl cbctl;

	/* prepare callback control */
	cbctl.sub_cmd = cmd;
	cbctl.param.vnic_char = vnicc;
	if (cmd == IPA_VNICC_SET_TIMEOUT)
		cbctl.param.timeout = *timeout;
	if (cmd == IPA_VNICC_GET_TIMEOUT)
		cbctl.result.timeout = timeout;

	QETH_CARD_TEXT(card, 2, "vniccgst");
	return qeth_l2_vnicc_request(card, &cbctl);
}