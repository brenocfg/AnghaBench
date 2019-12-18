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
#define  HPI_ISTREAM_GET_INFO 133 
#define  HPI_ISTREAM_HOSTBUFFER_ALLOC 132 
#define  HPI_ISTREAM_HOSTBUFFER_FREE 131 
#define  HPI_ISTREAM_HOSTBUFFER_GET_INFO 130 
#define  HPI_ISTREAM_READ 129 
#define  HPI_ISTREAM_START 128 
 scalar_t__ HPI_MAX_STREAMS ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_get_info (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_host_buffer_allocate (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_host_buffer_free (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_host_buffer_get_info (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_read (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_start (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void instream_message(struct hpi_adapter_obj *pao,
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
	case HPI_ISTREAM_READ:
		instream_read(pao, phm, phr);
		break;
	case HPI_ISTREAM_GET_INFO:
		instream_get_info(pao, phm, phr);
		break;
	case HPI_ISTREAM_HOSTBUFFER_ALLOC:
		instream_host_buffer_allocate(pao, phm, phr);
		break;
	case HPI_ISTREAM_HOSTBUFFER_GET_INFO:
		instream_host_buffer_get_info(pao, phm, phr);
		break;
	case HPI_ISTREAM_HOSTBUFFER_FREE:
		instream_host_buffer_free(pao, phm, phr);
		break;
	case HPI_ISTREAM_START:
		instream_start(pao, phm, phr);
		break;
	default:
		hw_message(pao, phm, phr);
		break;
	}
}