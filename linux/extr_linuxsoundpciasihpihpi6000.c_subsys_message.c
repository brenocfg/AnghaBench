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
struct hpi_message {int function; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_FUNC ; 
#define  HPI_SUBSYS_CREATE_ADAPTER 128 
 int /*<<< orphan*/  subsys_create_adapter (struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void subsys_message(struct hpi_message *phm, struct hpi_response *phr)
{
	switch (phm->function) {
	case HPI_SUBSYS_CREATE_ADAPTER:
		subsys_create_adapter(phm, phr);
		break;
	default:
		phr->error = HPI_ERROR_INVALID_FUNC;
		break;
	}
}