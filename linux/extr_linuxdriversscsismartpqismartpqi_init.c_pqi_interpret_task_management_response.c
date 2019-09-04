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
struct pqi_task_management_response {int response_code; } ;

/* Variables and functions */
 int EIO ; 
#define  SOP_TMF_COMPLETE 129 
#define  SOP_TMF_FUNCTION_SUCCEEDED 128 

__attribute__((used)) static int pqi_interpret_task_management_response(
	struct pqi_task_management_response *response)
{
	int rc;

	switch (response->response_code) {
	case SOP_TMF_COMPLETE:
	case SOP_TMF_FUNCTION_SUCCEEDED:
		rc = 0;
		break;
	default:
		rc = -EIO;
		break;
	}

	return rc;
}