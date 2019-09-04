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
struct se_cmd {unsigned char* t_task_cdb; int /*<<< orphan*/  data_length; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
#define  RCR_SA_COPY_STATUS 131 
#define  RCR_SA_FAILED_SEGMENT_DETAILS 130 
#define  RCR_SA_OPERATING_PARAMETERS 129 
#define  RCR_SA_RECEIVE_DATA 128 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_NO_SENSE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  target_rcr_operating_parameters (struct se_cmd*) ; 

sense_reason_t target_do_receive_copy_results(struct se_cmd *se_cmd)
{
	unsigned char *cdb = &se_cmd->t_task_cdb[0];
	int sa = (cdb[1] & 0x1f), list_id = cdb[2];
	sense_reason_t rc = TCM_NO_SENSE;

	pr_debug("Entering target_do_receive_copy_results: SA: 0x%02x, List ID:"
		" 0x%02x, AL: %u\n", sa, list_id, se_cmd->data_length);

	if (list_id != 0) {
		pr_err("Receive Copy Results with non zero list identifier"
		       " not supported\n");
		return TCM_INVALID_CDB_FIELD;
	}

	switch (sa) {
	case RCR_SA_OPERATING_PARAMETERS:
		rc = target_rcr_operating_parameters(se_cmd);
		break;
	case RCR_SA_COPY_STATUS:
	case RCR_SA_RECEIVE_DATA:
	case RCR_SA_FAILED_SEGMENT_DETAILS:
	default:
		pr_err("Unsupported SA for receive copy results: 0x%02x\n", sa);
		return TCM_INVALID_CDB_FIELD;
	}

	return rc;
}