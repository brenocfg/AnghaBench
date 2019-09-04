#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct beiscsi_hba {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_IN_TPE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int POST_ERR_RECOVERY_CODE_MASK ; 
 int POST_STAGE_MASK ; 
 int POST_STAGE_RECOVERABLE_ERR ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,int) ; 
 int beiscsi_get_post_stage (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int beiscsi_detect_tpe(struct beiscsi_hba *phba)
{
	u32 post, status;
	int ret = 0;

	post = beiscsi_get_post_stage(phba);
	status = post & POST_STAGE_MASK;
	if ((status & POST_ERR_RECOVERY_CODE_MASK) ==
	    POST_STAGE_RECOVERABLE_ERR) {
		set_bit(BEISCSI_HBA_IN_TPE, &phba->state);
		__beiscsi_log(phba, KERN_INFO,
			      "BC_%d : HBA error recoverable: 0x%x\n", post);
		ret = 1;
	} else {
		__beiscsi_log(phba, KERN_INFO,
			      "BC_%d : HBA in UE: 0x%x\n", post);
	}

	return ret;
}