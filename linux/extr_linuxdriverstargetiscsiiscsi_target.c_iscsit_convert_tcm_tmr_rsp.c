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
typedef  int /*<<< orphan*/  u8 ;
struct se_tmr_req {int response; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_TMF_RSP_COMPLETE ; 
 int /*<<< orphan*/  ISCSI_TMF_RSP_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ISCSI_TMF_RSP_NO_LUN ; 
 int /*<<< orphan*/  ISCSI_TMF_RSP_NO_TASK ; 
 int /*<<< orphan*/  ISCSI_TMF_RSP_REJECTED ; 
#define  TMR_FUNCTION_COMPLETE 132 
#define  TMR_FUNCTION_REJECTED 131 
#define  TMR_LUN_DOES_NOT_EXIST 130 
#define  TMR_TASK_DOES_NOT_EXIST 129 
#define  TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED 128 

__attribute__((used)) static u8 iscsit_convert_tcm_tmr_rsp(struct se_tmr_req *se_tmr)
{
	switch (se_tmr->response) {
	case TMR_FUNCTION_COMPLETE:
		return ISCSI_TMF_RSP_COMPLETE;
	case TMR_TASK_DOES_NOT_EXIST:
		return ISCSI_TMF_RSP_NO_TASK;
	case TMR_LUN_DOES_NOT_EXIST:
		return ISCSI_TMF_RSP_NO_LUN;
	case TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED:
		return ISCSI_TMF_RSP_NOT_SUPPORTED;
	case TMR_FUNCTION_REJECTED:
	default:
		return ISCSI_TMF_RSP_REJECTED;
	}
}