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
struct TYPE_7__ {scalar_t__ param2; scalar_t__ param1; } ;
struct TYPE_8__ {TYPE_3__ c; } ;
struct hpi_response {scalar_t__ error; TYPE_4__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  attribute; } ;
struct TYPE_6__ {TYPE_1__ c; } ;
struct hpi_message {TYPE_2__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_BITSTREAM_ACTIVITY ; 
 int /*<<< orphan*/  HPI_CONTROL_GET_STATE ; 
 scalar_t__ HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_bitstream_get_activity(u32 h_control, u16 *pw_clk_activity,
	u16 *pw_data_activity)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	if (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_BITSTREAM_ACTIVITY;
	hpi_send_recv(&hm, &hr);
	if (pw_clk_activity)
		*pw_clk_activity = (u16)hr.u.c.param1;
	if (pw_data_activity)
		*pw_data_activity = (u16)hr.u.c.param2;
	return hr.error;
}