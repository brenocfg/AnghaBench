#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  serial_number; int /*<<< orphan*/  version; int /*<<< orphan*/  num_instreams; int /*<<< orphan*/  num_outstreams; int /*<<< orphan*/  adapter_type; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ ax; } ;
struct hpi_response {int /*<<< orphan*/  error; TYPE_3__ u; } ;
struct hpi_message {int /*<<< orphan*/  adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_GET_INFO ; 
 int /*<<< orphan*/  HPI_OBJ_ADAPTER ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_adapter_get_info(u16 adapter_index, u16 *pw_num_outstreams,
	u16 *pw_num_instreams, u16 *pw_version, u32 *pserial_number,
	u16 *pw_adapter_type)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_INFO);
	hm.adapter_index = adapter_index;

	hpi_send_recv(&hm, &hr);

	*pw_adapter_type = hr.u.ax.info.adapter_type;
	*pw_num_outstreams = hr.u.ax.info.num_outstreams;
	*pw_num_instreams = hr.u.ax.info.num_instreams;
	*pw_version = hr.u.ax.info.version;
	*pserial_number = hr.u.ax.info.serial_number;
	return hr.error;
}