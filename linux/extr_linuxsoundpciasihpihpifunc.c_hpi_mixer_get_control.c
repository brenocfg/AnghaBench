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
typedef  void* u16 ;
struct TYPE_7__ {int /*<<< orphan*/  control_index; } ;
struct TYPE_8__ {TYPE_3__ m; } ;
struct hpi_response {scalar_t__ error; TYPE_4__ u; } ;
struct TYPE_5__ {void* control_type; void* node_index2; void* node_type2; void* node_index1; void* node_type1; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct hpi_message {int /*<<< orphan*/  adapter_index; TYPE_2__ u; } ;

/* Variables and functions */
 void* HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_MIXER_GET_CONTROL ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 int /*<<< orphan*/  HPI_OBJ_MIXER ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_indexes_to_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_mixer_get_control(u32 h_mixer, u16 src_node_type,
	u16 src_node_type_index, u16 dst_node_type, u16 dst_node_type_index,
	u16 control_type, u32 *ph_control)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER,
		HPI_MIXER_GET_CONTROL);
	if (hpi_handle_indexes(h_mixer, &hm.adapter_index, NULL))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.m.node_type1 = src_node_type;
	hm.u.m.node_index1 = src_node_type_index;
	hm.u.m.node_type2 = dst_node_type;
	hm.u.m.node_index2 = dst_node_type_index;
	hm.u.m.control_type = control_type;

	hpi_send_recv(&hm, &hr);

	if (hr.error == 0)
		*ph_control =
			hpi_indexes_to_handle(HPI_OBJ_CONTROL,
			hm.adapter_index, hr.u.m.control_index);
	else
		*ph_control = 0;
	return hr.error;
}