#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct TYPE_10__ {scalar_t__ serial_number; void* version; void* num_instreams; void* num_outstreams; void* adapter_type; } ;
struct TYPE_11__ {TYPE_4__ info; } ;
struct TYPE_12__ {TYPE_5__ ax; } ;
struct hpi_response {void* error; TYPE_6__ u; } ;
struct TYPE_7__ {void* index; } ;
struct TYPE_8__ {TYPE_1__ module_info; } ;
struct TYPE_9__ {TYPE_2__ ax; } ;
struct hpi_message {TYPE_3__ u; void* adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_MODULE_INFO ; 
 int /*<<< orphan*/  HPI_OBJ_ADAPTER ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_adapter_get_module_by_index(u16 adapter_index, u16 module_index,
	u16 *pw_num_outputs, u16 *pw_num_inputs, u16 *pw_version,
	u32 *pserial_number, u16 *pw_module_type, u32 *ph_module)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_MODULE_INFO);
	hm.adapter_index = adapter_index;
	hm.u.ax.module_info.index = module_index;

	hpi_send_recv(&hm, &hr);

	*pw_module_type = hr.u.ax.info.adapter_type;
	*pw_num_outputs = hr.u.ax.info.num_outstreams;
	*pw_num_inputs = hr.u.ax.info.num_instreams;
	*pw_version = hr.u.ax.info.version;
	*pserial_number = hr.u.ax.info.serial_number;
	*ph_module = 0;

	return hr.error;
}