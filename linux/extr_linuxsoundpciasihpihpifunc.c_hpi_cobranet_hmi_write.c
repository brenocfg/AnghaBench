#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct hpi_response_header {scalar_t__ error; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;
struct TYPE_4__ {int byte_count; int hmi_address; int /*<<< orphan*/  attribute; } ;
struct hpi_msg_cobranet_hmiwrite {TYPE_2__ h; int /*<<< orphan*/  bytes; TYPE_1__ p; } ;
typedef  int /*<<< orphan*/  hr ;
typedef  int /*<<< orphan*/  hm ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_COBRANET_SET ; 
 int /*<<< orphan*/  HPI_CONTROL_SET_STATE ; 
 scalar_t__ HPI_ERROR_INVALID_HANDLE ; 
 scalar_t__ HPI_ERROR_MESSAGE_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 scalar_t__ hpi_handle_indexes (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_responseV1 (TYPE_2__*,int,struct hpi_response_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recvV1 (TYPE_2__*,struct hpi_response_header*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

u16 hpi_cobranet_hmi_write(u32 h_control, u32 hmi_address, u32 byte_count,
	u8 *pb_data)
{
	struct hpi_msg_cobranet_hmiwrite hm;
	struct hpi_response_header hr;

	hpi_init_message_responseV1(&hm.h, sizeof(hm), &hr, sizeof(hr),
		HPI_OBJ_CONTROL, HPI_CONTROL_SET_STATE);

	if (hpi_handle_indexes(h_control, &hm.h.adapter_index,
			&hm.h.obj_index))
		return HPI_ERROR_INVALID_HANDLE;

	if (byte_count > sizeof(hm.bytes))
		return HPI_ERROR_MESSAGE_BUFFER_TOO_SMALL;

	hm.p.attribute = HPI_COBRANET_SET;
	hm.p.byte_count = byte_count;
	hm.p.hmi_address = hmi_address;
	memcpy(hm.bytes, pb_data, byte_count);
	hm.h.size = (u16)(sizeof(hm.h) + sizeof(hm.p) + byte_count);

	hpi_send_recvV1(&hm.h, &hr);
	return hr.error;
}