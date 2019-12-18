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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hpi_response {int /*<<< orphan*/  error; } ;
struct TYPE_5__ {int data_size; int /*<<< orphan*/ * pb_data; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_message {TYPE_4__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;
struct hpi_anc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_DATASIZE ; 
 int /*<<< orphan*/  HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_ISTREAM_ANC_WRITE ; 
 int /*<<< orphan*/  HPI_OBJ_ISTREAM ; 
 scalar_t__ hpi_handle_indexes (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_instream_ancillary_write(u32 h_instream,
	const struct hpi_anc_frame *p_anc_frame_buffer,
	u32 anc_frame_buffer_size_in_bytes,
	u32 number_of_ancillary_frames_to_write)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_ANC_WRITE);
	if (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.pb_data = (u8 *)p_anc_frame_buffer;
	hm.u.d.u.data.data_size =
		number_of_ancillary_frames_to_write *
		sizeof(struct hpi_anc_frame);
	if (hm.u.d.u.data.data_size <= anc_frame_buffer_size_in_bytes)
		hpi_send_recv(&hm, &hr);
	else
		hr.error = HPI_ERROR_INVALID_DATASIZE;
	return hr.error;
}