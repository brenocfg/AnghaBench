#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct hpi_response {int error; } ;
struct TYPE_6__ {int attributes; int format; int channels; } ;
struct TYPE_7__ {TYPE_1__ format; } ;
struct TYPE_8__ {TYPE_2__ data; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
struct TYPE_10__ {TYPE_4__ d; } ;
struct hpi_message {TYPE_5__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_ISTREAM_ANC_RESET ; 
 int /*<<< orphan*/  HPI_OBJ_ISTREAM ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_instream_ancillary_reset(u32 h_instream, u16 bytes_per_frame,
	u16 mode, u16 alignment, u16 idle_bit)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_ANC_RESET);
	if (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.format.attributes = bytes_per_frame;
	hm.u.d.u.data.format.format = (mode << 8) | (alignment & 0xff);
	hm.u.d.u.data.format.channels = idle_bit;
	hpi_send_recv(&hm, &hr);
	return hr.error;
}