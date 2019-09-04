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
struct hpi_response {int dummy; } ;
struct hpi_message {scalar_t__ obj_index; size_t adapter_index; int function; } ;
struct TYPE_2__ {scalar_t__ num_outstreams; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_OBJ_INDEX ; 
 int /*<<< orphan*/  HPI_OBJ_OSTREAM ; 
#define  HPI_OSTREAM_CLOSE 129 
#define  HPI_OSTREAM_OPEN 128 
 TYPE_1__* aDAPTER_INFO ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_entry_point (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_close (struct hpi_message*,struct hpi_response*,void*) ; 
 int /*<<< orphan*/  outstream_open (struct hpi_message*,struct hpi_response*,void*) ; 

__attribute__((used)) static void outstream_message(struct hpi_message *phm,
	struct hpi_response *phr, void *h_owner)
{
	if (phm->obj_index >= aDAPTER_INFO[phm->adapter_index].num_outstreams) {
		hpi_init_response(phr, HPI_OBJ_OSTREAM, phm->function,
			HPI_ERROR_INVALID_OBJ_INDEX);
		return;
	}

	switch (phm->function) {
	case HPI_OSTREAM_OPEN:
		outstream_open(phm, phr, h_owner);
		break;
	case HPI_OSTREAM_CLOSE:
		outstream_close(phm, phr, h_owner);
		break;
	default:
		hw_entry_point(phm, phr);
		break;
	}
}