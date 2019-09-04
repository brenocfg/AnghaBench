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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int /*<<< orphan*/  an_log_value; } ;
struct TYPE_8__ {TYPE_3__ c; } ;
struct hpi_response {int /*<<< orphan*/  error; TYPE_4__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  attribute; } ;
struct TYPE_6__ {TYPE_1__ c; } ;
struct hpi_message {TYPE_2__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_CONTROL_GET_STATE ; 
 int /*<<< orphan*/  HPI_ERROR_INVALID_HANDLE ; 
 int HPI_MAX_CHANNELS ; 
 short HPI_METER_MINIMUM ; 
 int /*<<< orphan*/  HPI_METER_PEAK ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  memcpy (short*,int /*<<< orphan*/ ,int) ; 

u16 hpi_meter_get_peak(u32 h_control, short an_peakdB[HPI_MAX_CHANNELS]
	)
{
	short i = 0;

	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	if (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hm.obj_index = hm.obj_index;
	hm.u.c.attribute = HPI_METER_PEAK;

	hpi_send_recv(&hm, &hr);

	if (!hr.error)
		memcpy(an_peakdB, hr.u.c.an_log_value,
			sizeof(short) * HPI_MAX_CHANNELS);
	else
		for (i = 0; i < HPI_MAX_CHANNELS; i++)
			an_peakdB[i] = HPI_METER_MINIMUM;
	return hr.error;
}