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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hpi_response {int /*<<< orphan*/  error; } ;
struct TYPE_5__ {void* punch_out_sample; void* punch_in_sample; } ;
struct TYPE_7__ {TYPE_1__ pio; } ;
struct TYPE_6__ {TYPE_3__ u; } ;
struct TYPE_8__ {TYPE_2__ d; } ;
struct hpi_message {TYPE_4__ u; int /*<<< orphan*/  obj_index; int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_OBJ_OSTREAM ; 
 int /*<<< orphan*/  HPI_OSTREAM_SET_PUNCHINOUT ; 
 scalar_t__ hpi_handle_indexes (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_outstream_set_punch_in_out(u32 h_outstream, u32 punch_in_sample,
	u32 punch_out_sample)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_SET_PUNCHINOUT);
	if (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		return HPI_ERROR_INVALID_HANDLE;

	hm.u.d.u.pio.punch_in_sample = punch_in_sample;
	hm.u.d.u.pio.punch_out_sample = punch_out_sample;

	hpi_send_recv(&hm, &hr);

	return hr.error;
}