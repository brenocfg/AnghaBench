#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_9__ {int /*<<< orphan*/  writeable_size; int /*<<< orphan*/  readable_size; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {TYPE_3__ status; } ;
struct TYPE_11__ {TYPE_4__ cobranet; } ;
struct TYPE_12__ {TYPE_5__ cu; } ;
struct hpi_response {int /*<<< orphan*/  error; TYPE_6__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  attribute; } ;
struct TYPE_8__ {TYPE_1__ c; } ;
struct hpi_message {TYPE_2__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_COBRANET_GET_STATUS ; 
 int /*<<< orphan*/  HPI_CONTROL_GET_STATE ; 
 int /*<<< orphan*/  HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_cobranet_hmi_get_status(u32 h_control, u32 *pstatus,
	u32 *preadable_size, u32 *pwriteable_size)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	if (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;

	hm.u.c.attribute = HPI_COBRANET_GET_STATUS;

	hpi_send_recv(&hm, &hr);
	if (!hr.error) {
		if (pstatus)
			*pstatus = hr.u.cu.cobranet.status.status;
		if (preadable_size)
			*preadable_size =
				hr.u.cu.cobranet.status.readable_size;
		if (pwriteable_size)
			*pwriteable_size =
				hr.u.cu.cobranet.status.writeable_size;
	}
	return hr.error;
}