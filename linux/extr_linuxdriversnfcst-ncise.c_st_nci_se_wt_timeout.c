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
typedef  int u8 ;
struct timer_list {int dummy; } ;
struct TYPE_5__ {int bwi_active; int xch_error; int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct st_nci_info {TYPE_2__ se_info; TYPE_1__* ndlc; } ;
struct TYPE_6__ {int /*<<< orphan*/  bwi_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  ST_NCI_APDU_READER_GATE ; 
 int /*<<< orphan*/  ST_NCI_DEVICE_MGNT_GATE ; 
 int /*<<< orphan*/  ST_NCI_EVT_SE_HARD_RESET ; 
 int /*<<< orphan*/  ST_NCI_EVT_SE_SOFT_RESET ; 
 struct st_nci_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct st_nci_info* info ; 
 int /*<<< orphan*/  nci_hci_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_3__ se_info ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st_nci_se_wt_timeout(struct timer_list *t)
{
	/*
	 * No answer from the secure element
	 * within the defined timeout.
	 * Let's send a reset request as recovery procedure.
	 * According to the situation, we first try to send a software reset
	 * to the secure element. If the next command is still not
	 * answering in time, we send to the CLF a secure element hardware
	 * reset request.
	 */
	/* hardware reset managed through VCC_UICC_OUT power supply */
	u8 param = 0x01;
	struct st_nci_info *info = from_timer(info, t, se_info.bwi_timer);

	pr_debug("\n");

	info->se_info.bwi_active = false;

	if (!info->se_info.xch_error) {
		info->se_info.xch_error = true;
		nci_hci_send_event(info->ndlc->ndev, ST_NCI_APDU_READER_GATE,
				ST_NCI_EVT_SE_SOFT_RESET, NULL, 0);
	} else {
		info->se_info.xch_error = false;
		nci_hci_send_event(info->ndlc->ndev, ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_EVT_SE_HARD_RESET, &param, 1);
	}
	info->se_info.cb(info->se_info.cb_context, NULL, 0, -ETIME);
}