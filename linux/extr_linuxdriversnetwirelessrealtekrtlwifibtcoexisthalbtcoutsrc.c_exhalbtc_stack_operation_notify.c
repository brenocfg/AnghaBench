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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cnt_stack_operation_notify; } ;
struct btc_coexist {scalar_t__ manual_control; TYPE_1__ statistics; } ;

/* Variables and functions */
 scalar_t__ BTC_STACK_OP_INQ_PAGE_PAIR_FINISH ; 
 scalar_t__ BTC_STACK_OP_INQ_PAGE_PAIR_START ; 
 scalar_t__ BTC_STACK_OP_NONE ; 
 scalar_t__ HCI_BT_OP_INQUIRY_FINISH ; 
 scalar_t__ HCI_BT_OP_INQUIRY_START ; 
 scalar_t__ HCI_BT_OP_PAGING_START ; 
 scalar_t__ HCI_BT_OP_PAGING_SUCCESS ; 
 scalar_t__ HCI_BT_OP_PAGING_UNSUCCESS ; 
 scalar_t__ HCI_BT_OP_PAIRING_FINISH ; 
 scalar_t__ HCI_BT_OP_PAIRING_START ; 
 int /*<<< orphan*/  halbtc_is_bt_coexist_available (struct btc_coexist*) ; 

void exhalbtc_stack_operation_notify(struct btc_coexist *btcoexist, u8 type)
{
	u8 stack_op_type;

	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;
	btcoexist->statistics.cnt_stack_operation_notify++;
	if (btcoexist->manual_control)
		return;

	if ((type == HCI_BT_OP_INQUIRY_START) ||
	    (type == HCI_BT_OP_PAGING_START) ||
	    (type == HCI_BT_OP_PAIRING_START)) {
		stack_op_type = BTC_STACK_OP_INQ_PAGE_PAIR_START;
	} else if ((type == HCI_BT_OP_INQUIRY_FINISH) ||
		   (type == HCI_BT_OP_PAGING_SUCCESS) ||
		   (type == HCI_BT_OP_PAGING_UNSUCCESS) ||
		   (type == HCI_BT_OP_PAIRING_FINISH)) {
		stack_op_type = BTC_STACK_OP_INQ_PAGE_PAIR_FINISH;
	} else {
		stack_op_type = BTC_STACK_OP_NONE;
	}
}