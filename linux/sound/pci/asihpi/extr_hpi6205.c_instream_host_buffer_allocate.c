#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_11__ {int data_available; int buffer_size; int /*<<< orphan*/  auxiliary_data_available; } ;
struct TYPE_12__ {TYPE_2__ stream_info; } ;
struct TYPE_13__ {TYPE_3__ u; } ;
struct TYPE_14__ {TYPE_4__ d; } ;
struct hpi_response {void* error; TYPE_5__ u; } ;
struct TYPE_15__ {scalar_t__ command; int buffer_size; int /*<<< orphan*/  pci_address; } ;
struct TYPE_16__ {TYPE_6__ buffer; } ;
struct TYPE_17__ {TYPE_7__ u; } ;
struct TYPE_18__ {TYPE_8__ d; } ;
struct hpi_message {size_t obj_index; TYPE_9__ u; int /*<<< orphan*/  function; int /*<<< orphan*/  object; } ;
struct hpi_hw_obj {int* instream_host_buffer_size; int /*<<< orphan*/ * instream_host_buffers; struct bus_master_interface* p_interface_buffer; } ;
struct hpi_hostbuffer_status {int size_in_bytes; scalar_t__ auxiliary_data_available; scalar_t__ dsp_index; scalar_t__ host_index; int /*<<< orphan*/  stream_state; scalar_t__ samples_processed; } ;
struct TYPE_10__ {int /*<<< orphan*/  pci_dev; } ;
struct hpi_adapter_obj {TYPE_1__ pci; struct hpi_hw_obj* priv; } ;
struct bus_master_interface {struct hpi_hostbuffer_status* instream_host_buffer_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HPI_BUFFER_CMD_EXTERNAL ; 
 scalar_t__ HPI_BUFFER_CMD_INTERNAL_ALLOC ; 
 scalar_t__ HPI_BUFFER_CMD_INTERNAL_GRANTADAPTER ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,int) ; 
 void* HPI_ERROR_INVALID_DATASIZE ; 
 void* HPI_ERROR_MEMORY_ALLOC ; 
 int /*<<< orphan*/  HPI_STATE_STOPPED ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hpios_locked_mem_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpios_locked_mem_free (int /*<<< orphan*/ *) ; 
 scalar_t__ hpios_locked_mem_get_phys_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hpios_locked_mem_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static void instream_host_buffer_allocate(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	u16 err = 0;
	u32 command = phm->u.d.u.buffer.command;
	struct hpi_hw_obj *phw = pao->priv;
	struct bus_master_interface *interface = phw->p_interface_buffer;

	hpi_init_response(phr, phm->object, phm->function, 0);

	if (command == HPI_BUFFER_CMD_EXTERNAL
		|| command == HPI_BUFFER_CMD_INTERNAL_ALLOC) {

		phm->u.d.u.buffer.buffer_size =
			roundup_pow_of_two(phm->u.d.u.buffer.buffer_size);
		phr->u.d.u.stream_info.data_available =
			phw->instream_host_buffer_size[phm->obj_index];
		phr->u.d.u.stream_info.buffer_size =
			phm->u.d.u.buffer.buffer_size;

		if (phw->instream_host_buffer_size[phm->obj_index] ==
			phm->u.d.u.buffer.buffer_size) {
			/* Same size, no action required */
			return;
		}

		if (hpios_locked_mem_valid(&phw->instream_host_buffers[phm->
					obj_index]))
			hpios_locked_mem_free(&phw->instream_host_buffers
				[phm->obj_index]);

		err = hpios_locked_mem_alloc(&phw->instream_host_buffers[phm->
				obj_index], phm->u.d.u.buffer.buffer_size,
			pao->pci.pci_dev);

		if (err) {
			phr->error = HPI_ERROR_INVALID_DATASIZE;
			phw->instream_host_buffer_size[phm->obj_index] = 0;
			return;
		}

		err = hpios_locked_mem_get_phys_addr
			(&phw->instream_host_buffers[phm->obj_index],
			&phm->u.d.u.buffer.pci_address);
		/* get the phys addr into msg for single call alloc. Caller
		   needs to do this for split alloc so return the phy address */
		phr->u.d.u.stream_info.auxiliary_data_available =
			phm->u.d.u.buffer.pci_address;
		if (err) {
			hpios_locked_mem_free(&phw->instream_host_buffers
				[phm->obj_index]);
			phw->instream_host_buffer_size[phm->obj_index] = 0;
			phr->error = HPI_ERROR_MEMORY_ALLOC;
			return;
		}
	}

	if (command == HPI_BUFFER_CMD_EXTERNAL
		|| command == HPI_BUFFER_CMD_INTERNAL_GRANTADAPTER) {
		struct hpi_hostbuffer_status *status;

		if (phm->u.d.u.buffer.buffer_size & (phm->u.d.u.buffer.
				buffer_size - 1)) {
			HPI_DEBUG_LOG(ERROR,
				"Buffer size must be 2^N not %d\n",
				phm->u.d.u.buffer.buffer_size);
			phr->error = HPI_ERROR_INVALID_DATASIZE;
			return;
		}

		phw->instream_host_buffer_size[phm->obj_index] =
			phm->u.d.u.buffer.buffer_size;
		status = &interface->instream_host_buffer_status[phm->
			obj_index];
		status->samples_processed = 0;
		status->stream_state = HPI_STATE_STOPPED;
		status->dsp_index = 0;
		status->host_index = status->dsp_index;
		status->size_in_bytes = phm->u.d.u.buffer.buffer_size;
		status->auxiliary_data_available = 0;

		hw_message(pao, phm, phr);

		if (phr->error
			&& hpios_locked_mem_valid(&phw->
				instream_host_buffers[phm->obj_index])) {
			hpios_locked_mem_free(&phw->instream_host_buffers
				[phm->obj_index]);
			phw->instream_host_buffer_size[phm->obj_index] = 0;
		}
	}
}