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
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  auxiliary_data_available; scalar_t__ data_available; scalar_t__ buffer_size; int /*<<< orphan*/  samples_transferred; scalar_t__ state; } ;
struct TYPE_6__ {TYPE_1__ stream_info; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_response {TYPE_4__ u; } ;
struct hpi_message {size_t obj_index; int /*<<< orphan*/  function; int /*<<< orphan*/  object; } ;
struct hpi_hw_obj {int /*<<< orphan*/ * outstream_host_buffer_size; struct bus_master_interface* p_interface_buffer; } ;
struct hpi_hostbuffer_status {int /*<<< orphan*/  auxiliary_data_available; scalar_t__ size_in_bytes; int /*<<< orphan*/  samples_processed; scalar_t__ stream_state; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;
struct bus_master_interface {struct hpi_hostbuffer_status* outstream_host_buffer_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 scalar_t__ outstream_get_space_available (struct hpi_hostbuffer_status*) ; 

__attribute__((used)) static void outstream_get_info(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct bus_master_interface *interface = phw->p_interface_buffer;
	struct hpi_hostbuffer_status *status;

	if (!phw->outstream_host_buffer_size[phm->obj_index]) {
		hw_message(pao, phm, phr);
		return;
	}

	hpi_init_response(phr, phm->object, phm->function, 0);

	status = &interface->outstream_host_buffer_status[phm->obj_index];

	phr->u.d.u.stream_info.state = (u16)status->stream_state;
	phr->u.d.u.stream_info.samples_transferred =
		status->samples_processed;
	phr->u.d.u.stream_info.buffer_size = status->size_in_bytes;
	phr->u.d.u.stream_info.data_available =
		status->size_in_bytes - outstream_get_space_available(status);
	phr->u.d.u.stream_info.auxiliary_data_available =
		status->auxiliary_data_available;
}