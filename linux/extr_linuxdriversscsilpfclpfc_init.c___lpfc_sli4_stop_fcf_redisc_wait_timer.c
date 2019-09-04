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
struct TYPE_2__ {int /*<<< orphan*/  redisc_wait; int /*<<< orphan*/  fcf_flag; } ;
struct lpfc_hba {TYPE_1__ fcf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_REDISC_PEND ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

void
__lpfc_sli4_stop_fcf_redisc_wait_timer(struct lpfc_hba *phba)
{
	/* Clear pending FCF rediscovery wait flag */
	phba->fcf.fcf_flag &= ~FCF_REDISC_PEND;

	/* Now, try to stop the timer */
	del_timer(&phba->fcf.redisc_wait);
}