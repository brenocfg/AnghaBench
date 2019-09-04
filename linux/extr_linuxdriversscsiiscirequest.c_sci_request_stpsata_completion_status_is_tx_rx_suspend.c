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

/* Variables and functions */
#define  SCU_TASK_DONE_BREAK_RCVD 135 
#define  SCU_TASK_DONE_INV_FIS_LEN 134 
#define  SCU_TASK_DONE_LF_ERR 133 
#define  SCU_TASK_DONE_LL_LF_TERM 132 
#define  SCU_TASK_DONE_LL_SY_TERM 131 
#define  SCU_TASK_DONE_MAX_PLD_ERR 130 
#define  SCU_TASK_DONE_UNEXP_FIS 129 
#define  SCU_TASK_DONE_UNEXP_SDBFIS 128 

__attribute__((used)) static int sci_request_stpsata_completion_status_is_tx_rx_suspend(
	unsigned int completion_status)
{
	switch (completion_status) {
	case SCU_TASK_DONE_LF_ERR:
	case SCU_TASK_DONE_LL_SY_TERM:
	case SCU_TASK_DONE_LL_LF_TERM:
	case SCU_TASK_DONE_BREAK_RCVD:
	case SCU_TASK_DONE_INV_FIS_LEN:
	case SCU_TASK_DONE_UNEXP_FIS:
	case SCU_TASK_DONE_UNEXP_SDBFIS:
	case SCU_TASK_DONE_MAX_PLD_ERR:
		return 1;
	}
	return 0;
}