#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int /*<<< orphan*/  error; } ;
struct hpi_res_cobranet_hmiread {int byte_count; TYPE_3__ h; int /*<<< orphan*/  bytes; } ;
struct TYPE_7__ {int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;
struct TYPE_6__ {int byte_count; int hmi_address; int /*<<< orphan*/  attribute; } ;
struct hpi_msg_cobranet_hmiread {TYPE_2__ h; TYPE_1__ p; } ;
typedef  int /*<<< orphan*/  hr ;
typedef  int /*<<< orphan*/  hm ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_COBRANET_GET ; 
 int /*<<< orphan*/  HPI_CONTROL_GET_STATE ; 
 int /*<<< orphan*/  HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 scalar_t__ hpi_handle_indexes (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_responseV1 (TYPE_2__*,int,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recvV1 (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u16 hpi_cobranet_hmi_read(u32 h_control, u32 hmi_address, u32 max_byte_count,
	u32 *pbyte_count, u8 *pb_data)
{
	struct hpi_msg_cobranet_hmiread hm;
	struct hpi_res_cobranet_hmiread hr;

	hpi_init_message_responseV1(&hm.h, sizeof(hm), &hr.h, sizeof(hr),
		HPI_OBJ_CONTROL, HPI_CONTROL_GET_STATE);

	if (hpi_handle_indexes(h_control, &hm.h.adapter_index,
			&hm.h.obj_index))
		return HPI_ERROR_INVALID_HANDLE;

	if (max_byte_count > sizeof(hr.bytes))
		return HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;

	hm.p.attribute = HPI_COBRANET_GET;
	hm.p.byte_count = max_byte_count;
	hm.p.hmi_address = hmi_address;

	hpi_send_recvV1(&hm.h, &hr.h);

	if (!hr.h.error && pb_data) {
		if (hr.byte_count > sizeof(hr.bytes))

			return HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;

		*pbyte_count = hr.byte_count;

		if (hr.byte_count < max_byte_count)
			max_byte_count = *pbyte_count;

		memcpy(pb_data, hr.bytes, max_byte_count);
	}
	return hr.h.error;
}