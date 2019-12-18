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
struct TYPE_7__ {int param2; short* an_log_value; int /*<<< orphan*/  param1; } ;
struct TYPE_8__ {TYPE_3__ c; } ;
struct hpi_response {scalar_t__ error; TYPE_4__ u; } ;
struct TYPE_5__ {scalar_t__ param2; int /*<<< orphan*/  attribute; } ;
struct TYPE_6__ {TYPE_1__ c; } ;
struct hpi_message {TYPE_2__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_CONTROL_GET_STATE ; 
 int /*<<< orphan*/  HPI_EQUALIZER_FILTER ; 
 scalar_t__ HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_parametric_eq_get_band(u32 h_control, u16 index, u16 *pn_type,
	u32 *pfrequency_hz, short *pnQ100, short *pn_gain0_01dB)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	if (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_EQUALIZER_FILTER;
	hm.u.c.param2 = index;

	hpi_send_recv(&hm, &hr);

	if (pfrequency_hz)
		*pfrequency_hz = hr.u.c.param1;
	if (pn_type)
		*pn_type = (u16)(hr.u.c.param2 >> 16);
	if (pnQ100)
		*pnQ100 = hr.u.c.an_log_value[1];
	if (pn_gain0_01dB)
		*pn_gain0_01dB = hr.u.c.an_log_value[0];

	return hr.error;
}