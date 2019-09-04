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
struct hisi_sas_slot {int dummy; } ;
struct hisi_hba {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* prep_abort ) (struct hisi_hba*,struct hisi_sas_slot*,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hisi_hba*,struct hisi_sas_slot*,int,int,int) ; 

__attribute__((used)) static void hisi_sas_task_prep_abort(struct hisi_hba *hisi_hba,
		struct hisi_sas_slot *slot,
		int device_id, int abort_flag, int tag_to_abort)
{
	hisi_hba->hw->prep_abort(hisi_hba, slot,
			device_id, abort_flag, tag_to_abort);
}