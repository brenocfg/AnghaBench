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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hpi_response {scalar_t__ error; } ;
struct TYPE_5__ {scalar_t__ data_size; scalar_t__ pb_data; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_message {size_t obj_index; TYPE_4__ u; int /*<<< orphan*/  function; int /*<<< orphan*/  object; } ;
struct hpi_hw_obj {scalar_t__* flag_outstream_just_reset; int /*<<< orphan*/ * outstream_host_buffers; int /*<<< orphan*/ * outstream_host_buffer_size; struct bus_master_interface* p_interface_buffer; } ;
struct hpi_hostbuffer_status {int size_in_bytes; int host_index; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;
struct bus_master_interface {struct hpi_hostbuffer_status* outstream_host_buffer_status; } ;

/* Variables and functions */
 scalar_t__ HPI_ERROR_INVALID_DATASIZE ; 
 scalar_t__ HPI_ERROR_INVALID_OPERATION ; 
 int /*<<< orphan*/  HPI_OSTREAM_SET_FORMAT ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hpios_locked_mem_get_virt_addr (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ hpios_locked_mem_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ min (scalar_t__,int) ; 
 scalar_t__ outstream_get_space_available (struct hpi_hostbuffer_status*) ; 

__attribute__((used)) static void outstream_write(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct bus_master_interface *interface = phw->p_interface_buffer;
	struct hpi_hostbuffer_status *status;
	u32 space_available;

	if (!phw->outstream_host_buffer_size[phm->obj_index]) {
		/* there  is no BBM buffer, write via message */
		hw_message(pao, phm, phr);
		return;
	}

	hpi_init_response(phr, phm->object, phm->function, 0);
	status = &interface->outstream_host_buffer_status[phm->obj_index];

	space_available = outstream_get_space_available(status);
	if (space_available < phm->u.d.u.data.data_size) {
		phr->error = HPI_ERROR_INVALID_DATASIZE;
		return;
	}

	/* HostBuffers is used to indicate host buffer is internally allocated.
	   otherwise, assumed external, data written externally */
	if (phm->u.d.u.data.pb_data
		&& hpios_locked_mem_valid(&phw->outstream_host_buffers[phm->
				obj_index])) {
		u8 *p_bbm_data;
		u32 l_first_write;
		u8 *p_app_data = (u8 *)phm->u.d.u.data.pb_data;

		if (hpios_locked_mem_get_virt_addr(&phw->
				outstream_host_buffers[phm->obj_index],
				(void *)&p_bbm_data)) {
			phr->error = HPI_ERROR_INVALID_OPERATION;
			return;
		}

		/* either all data,
		   or enough to fit from current to end of BBM buffer */
		l_first_write =
			min(phm->u.d.u.data.data_size,
			status->size_in_bytes -
			(status->host_index & (status->size_in_bytes - 1)));

		memcpy(p_bbm_data +
			(status->host_index & (status->size_in_bytes - 1)),
			p_app_data, l_first_write);
		/* remaining data if any */
		memcpy(p_bbm_data, p_app_data + l_first_write,
			phm->u.d.u.data.data_size - l_first_write);
	}

	/*
	 * This version relies on the DSP code triggering an OStream buffer
	 * update immediately following a SET_FORMAT call. The host has
	 * already written data into the BBM buffer, but the DSP won't know
	 * about it until dwHostIndex is adjusted.
	 */
	if (phw->flag_outstream_just_reset[phm->obj_index]) {
		/* Format can only change after reset. Must tell DSP. */
		u16 function = phm->function;
		phw->flag_outstream_just_reset[phm->obj_index] = 0;
		phm->function = HPI_OSTREAM_SET_FORMAT;
		hw_message(pao, phm, phr);	/* send the format to the DSP */
		phm->function = function;
		if (phr->error)
			return;
	}

	status->host_index += phm->u.d.u.data.data_size;
}