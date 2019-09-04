#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int uchar ;
struct TYPE_3__ {int unit_not_ready; int queue_full_or_busy; int last_q_shortage; int max_total_qng; scalar_t__* cur_dvc_qng; scalar_t__* max_dvc_qng; scalar_t__ cur_total_qng; } ;
typedef  int ASC_SCSI_BIT_ID_TYPE ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */
 int ASC_MIN_FREE_Q ; 
 int ASC_TIX_TO_TARGET_ID (int) ; 
 int ASC_TIX_TO_TID (int) ; 

__attribute__((used)) static uint
AscGetNumOfFreeQueue(ASC_DVC_VAR *asc_dvc, uchar target_ix, uchar n_qs)
{
	uint cur_used_qs;
	uint cur_free_qs;
	ASC_SCSI_BIT_ID_TYPE target_id;
	uchar tid_no;

	target_id = ASC_TIX_TO_TARGET_ID(target_ix);
	tid_no = ASC_TIX_TO_TID(target_ix);
	if ((asc_dvc->unit_not_ready & target_id) ||
	    (asc_dvc->queue_full_or_busy & target_id)) {
		return 0;
	}
	if (n_qs == 1) {
		cur_used_qs = (uint) asc_dvc->cur_total_qng +
		    (uint) asc_dvc->last_q_shortage + (uint) ASC_MIN_FREE_Q;
	} else {
		cur_used_qs = (uint) asc_dvc->cur_total_qng +
		    (uint) ASC_MIN_FREE_Q;
	}
	if ((uint) (cur_used_qs + n_qs) <= (uint) asc_dvc->max_total_qng) {
		cur_free_qs = (uint) asc_dvc->max_total_qng - cur_used_qs;
		if (asc_dvc->cur_dvc_qng[tid_no] >=
		    asc_dvc->max_dvc_qng[tid_no]) {
			return 0;
		}
		return cur_free_qs;
	}
	if (n_qs > 1) {
		if ((n_qs > asc_dvc->last_q_shortage)
		    && (n_qs <= (asc_dvc->max_total_qng - ASC_MIN_FREE_Q))) {
			asc_dvc->last_q_shortage = n_qs;
		}
	}
	return 0;
}