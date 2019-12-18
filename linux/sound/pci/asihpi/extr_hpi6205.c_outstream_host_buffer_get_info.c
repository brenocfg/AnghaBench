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
struct TYPE_5__ {struct hpi_hostbuffer_status* p_status; int /*<<< orphan*/ * p_buffer; } ;
struct TYPE_6__ {TYPE_1__ hostbuffer_info; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_response {TYPE_4__ u; int /*<<< orphan*/  error; } ;
struct hpi_message {size_t obj_index; } ;
struct hpi_hw_obj {int /*<<< orphan*/ * outstream_host_buffers; struct bus_master_interface* p_interface_buffer; } ;
struct hpi_hostbuffer_status {int dummy; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;
struct bus_master_interface {struct hpi_hostbuffer_status* outstream_host_buffer_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_OPERATION ; 
 int /*<<< orphan*/  HPI_OBJ_OSTREAM ; 
 int /*<<< orphan*/  HPI_OSTREAM_HOSTBUFFER_GET_INFO ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hpios_locked_mem_get_virt_addr (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ hpios_locked_mem_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void outstream_host_buffer_get_info(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct bus_master_interface *interface = phw->p_interface_buffer;
	struct hpi_hostbuffer_status *status;
	u8 *p_bbm_data;

	if (hpios_locked_mem_valid(&phw->outstream_host_buffers[phm->
				obj_index])) {
		if (hpios_locked_mem_get_virt_addr(&phw->
				outstream_host_buffers[phm->obj_index],
				(void *)&p_bbm_data)) {
			phr->error = HPI_ERROR_INVALID_OPERATION;
			return;
		}
		status = &interface->outstream_host_buffer_status[phm->
			obj_index];
		hpi_init_response(phr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_HOSTBUFFER_GET_INFO, 0);
		phr->u.d.u.hostbuffer_info.p_buffer = p_bbm_data;
		phr->u.d.u.hostbuffer_info.p_status = status;
	} else {
		hpi_init_response(phr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_HOSTBUFFER_GET_INFO,
			HPI_ERROR_INVALID_OPERATION);
	}
}