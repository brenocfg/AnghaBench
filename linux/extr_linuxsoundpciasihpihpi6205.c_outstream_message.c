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
struct hpi_message {scalar_t__ obj_index; int function; int /*<<< orphan*/  adapter_index; } ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPI_ERROR_INVALID_OBJ_INDEX ; 
 scalar_t__ HPI_MAX_STREAMS ; 
#define  HPI_OSTREAM_GET_INFO 135 
#define  HPI_OSTREAM_HOSTBUFFER_ALLOC 134 
#define  HPI_OSTREAM_HOSTBUFFER_FREE 133 
#define  HPI_OSTREAM_HOSTBUFFER_GET_INFO 132 
#define  HPI_OSTREAM_OPEN 131 
#define  HPI_OSTREAM_RESET 130 
#define  HPI_OSTREAM_START 129 
#define  HPI_OSTREAM_WRITE 128 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_get_info (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_host_buffer_allocate (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_host_buffer_free (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_host_buffer_get_info (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_open (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_reset (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_start (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_write (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void outstream_message(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{

	if (phm->obj_index >= HPI_MAX_STREAMS) {
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
		HPI_DEBUG_LOG(WARNING,
			"Message referencing invalid stream %d "
			"on adapter index %d\n", phm->obj_index,
			phm->adapter_index);
		return;
	}

	switch (phm->function) {
	case HPI_OSTREAM_WRITE:
		outstream_write(pao, phm, phr);
		break;
	case HPI_OSTREAM_GET_INFO:
		outstream_get_info(pao, phm, phr);
		break;
	case HPI_OSTREAM_HOSTBUFFER_ALLOC:
		outstream_host_buffer_allocate(pao, phm, phr);
		break;
	case HPI_OSTREAM_HOSTBUFFER_GET_INFO:
		outstream_host_buffer_get_info(pao, phm, phr);
		break;
	case HPI_OSTREAM_HOSTBUFFER_FREE:
		outstream_host_buffer_free(pao, phm, phr);
		break;
	case HPI_OSTREAM_START:
		outstream_start(pao, phm, phr);
		break;
	case HPI_OSTREAM_OPEN:
		outstream_open(pao, phm, phr);
		break;
	case HPI_OSTREAM_RESET:
		outstream_reset(pao, phm, phr);
		break;
	default:
		hw_message(pao, phm, phr);
		break;
	}
}