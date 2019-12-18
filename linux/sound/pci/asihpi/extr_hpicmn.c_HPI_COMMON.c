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
struct hpi_response {int /*<<< orphan*/  error; } ;
struct hpi_message {int type; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_TYPE ; 
#define  HPI_OBJ_SUBSYSTEM 129 
#define  HPI_TYPE_REQUEST 128 
 int /*<<< orphan*/  subsys_message (struct hpi_message*,struct hpi_response*) ; 

void HPI_COMMON(struct hpi_message *phm, struct hpi_response *phr)
{
	switch (phm->type) {
	case HPI_TYPE_REQUEST:
		switch (phm->object) {
		case HPI_OBJ_SUBSYSTEM:
			subsys_message(phm, phr);
			break;
		}
		break;

	default:
		phr->error = HPI_ERROR_INVALID_TYPE;
		break;
	}
}