#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct hpi_response {scalar_t__ error; } ;
struct TYPE_5__ {char object_type; int /*<<< orphan*/  stream_index; } ;
struct TYPE_6__ {TYPE_1__ stream; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_message {scalar_t__ adapter_index; TYPE_4__ u; int /*<<< orphan*/  obj_index; } ;

/* Variables and functions */
 scalar_t__ HPI_ERROR_INVALID_HANDLE ; 
 scalar_t__ HPI_ERROR_INVALID_OBJ ; 
 scalar_t__ HPI_ERROR_NO_INTERADAPTER_GROUPS ; 
 int /*<<< orphan*/  HPI_ISTREAM_GROUP_ADD ; 
#define  HPI_OBJ_ISTREAM 129 
#define  HPI_OBJ_OSTREAM 128 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 char hpi_handle_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_instream_group_add(u32 h_instream, u32 h_stream)
{
	struct hpi_message hm;
	struct hpi_response hr;
	u16 adapter;
	char c_obj_type;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_GROUP_ADD);
	hr.error = 0;

	if (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;

	if (hpi_handle_indexes(h_stream, &adapter,
			&hm.u.d.u.stream.stream_index))
		return HPI_ERROR_INVALID_HANDLE;

	c_obj_type = hpi_handle_object(h_stream);

	switch (c_obj_type) {
	case HPI_OBJ_OSTREAM:
	case HPI_OBJ_ISTREAM:
		hm.u.d.u.stream.object_type = c_obj_type;
		break;
	default:
		return HPI_ERROR_INVALID_OBJ;
	}

	if (adapter != hm.adapter_index)
		return HPI_ERROR_NO_INTERADAPTER_GROUPS;

	hpi_send_recv(&hm, &hr);
	return hr.error;
}