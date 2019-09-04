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
struct pqi_raid_error_info {int data_out_result; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 int PQI_CMD_STATUS_ABORTED ; 
#define  PQI_DATA_IN_OUT_ABORTED 130 
#define  PQI_DATA_IN_OUT_GOOD 129 
#define  PQI_DATA_IN_OUT_UNDERFLOW 128 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 

__attribute__((used)) static int pqi_process_raid_io_error_synchronous(struct pqi_raid_error_info
						*error_info)
{
	int rc = -EIO;

	switch (error_info->data_out_result) {
	case PQI_DATA_IN_OUT_GOOD:
		if (error_info->status == SAM_STAT_GOOD)
			rc = 0;
		break;
	case PQI_DATA_IN_OUT_UNDERFLOW:
		if (error_info->status == SAM_STAT_GOOD ||
			error_info->status == SAM_STAT_CHECK_CONDITION)
			rc = 0;
		break;
	case PQI_DATA_IN_OUT_ABORTED:
		rc = PQI_CMD_STATUS_ABORTED;
		break;
	}

	return rc;
}