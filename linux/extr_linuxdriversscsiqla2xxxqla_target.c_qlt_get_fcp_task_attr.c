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
typedef  int uint8_t ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
#define  ATIO_ACA_QUEUE 132 
#define  ATIO_HEAD_OF_QUEUE 131 
#define  ATIO_ORDERED_QUEUE 130 
#define  ATIO_SIMPLE_QUEUE 129 
#define  ATIO_UNTAGGED 128 
 int TCM_ACA_TAG ; 
 int TCM_HEAD_TAG ; 
 int TCM_ORDERED_TAG ; 
 int TCM_SIMPLE_TAG ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 

__attribute__((used)) static inline int qlt_get_fcp_task_attr(struct scsi_qla_host *vha,
	uint8_t task_codes)
{
	int fcp_task_attr;

	switch (task_codes) {
	case ATIO_SIMPLE_QUEUE:
		fcp_task_attr = TCM_SIMPLE_TAG;
		break;
	case ATIO_HEAD_OF_QUEUE:
		fcp_task_attr = TCM_HEAD_TAG;
		break;
	case ATIO_ORDERED_QUEUE:
		fcp_task_attr = TCM_ORDERED_TAG;
		break;
	case ATIO_ACA_QUEUE:
		fcp_task_attr = TCM_ACA_TAG;
		break;
	case ATIO_UNTAGGED:
		fcp_task_attr = TCM_SIMPLE_TAG;
		break;
	default:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf05d,
		    "qla_target: unknown task code %x, use ORDERED instead\n",
		    task_codes);
		fcp_task_attr = TCM_ORDERED_TAG;
		break;
	}

	return fcp_task_attr;
}