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
struct TYPE_5__ {int /*<<< orphan*/  auxiliary_data_available; int /*<<< orphan*/  samples_transferred; int /*<<< orphan*/  data_available; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_1__ stream_info; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_response {int /*<<< orphan*/  error; TYPE_4__ u; } ;
struct hpi_message {int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_ISTREAM_GET_INFO ; 
 int /*<<< orphan*/  HPI_OBJ_ISTREAM ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_instream_get_info_ex(u32 h_instream, u16 *pw_state, u32 *pbuffer_size,
	u32 *pdata_recorded, u32 *psamples_recorded,
	u32 *pauxiliary_data_recorded)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_GET_INFO);
	if (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	if (pw_state)
		*pw_state = hr.u.d.u.stream_info.state;
	if (pbuffer_size)
		*pbuffer_size = hr.u.d.u.stream_info.buffer_size;
	if (pdata_recorded)
		*pdata_recorded = hr.u.d.u.stream_info.data_available;
	if (psamples_recorded)
		*psamples_recorded = hr.u.d.u.stream_info.samples_transferred;
	if (pauxiliary_data_recorded)
		*pauxiliary_data_recorded =
			hr.u.d.u.stream_info.auxiliary_data_available;
	return hr.error;
}