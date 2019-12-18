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
typedef  scalar_t__ u16 ;
struct TYPE_7__ {scalar_t__ src_node_type; scalar_t__ src_node_index; scalar_t__ dst_node_type; scalar_t__ dst_node_index; scalar_t__ control_index; } ;
struct TYPE_8__ {TYPE_3__ m; } ;
struct hpi_response {scalar_t__ error; TYPE_4__ u; } ;
struct TYPE_5__ {scalar_t__ control_index; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct hpi_message {int /*<<< orphan*/  adapter_index; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ HPI_DESTNODE_NONE ; 
 scalar_t__ HPI_ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  HPI_MIXER_GET_CONTROL_BY_INDEX ; 
 int /*<<< orphan*/  HPI_OBJ_CONTROL ; 
 int /*<<< orphan*/  HPI_OBJ_MIXER ; 
 scalar_t__ HPI_SOURCENODE_NONE ; 
 scalar_t__ hpi_handle_indexes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpi_indexes_to_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_mixer_get_control_by_index(u32 h_mixer, u16 control_index,
	u16 *pw_src_node_type, u16 *pw_src_node_index, u16 *pw_dst_node_type,
	u16 *pw_dst_node_index, u16 *pw_control_type, u32 *ph_control)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER,
		HPI_MIXER_GET_CONTROL_BY_INDEX);
	if (hpi_handle_indexes(h_mixer, &hm.adapter_index, NULL))
		return HPI_ERROR_INVALID_HANDLE;
	hm.u.m.control_index = control_index;
	hpi_send_recv(&hm, &hr);

	if (pw_src_node_type) {
		*pw_src_node_type =
			hr.u.m.src_node_type + HPI_SOURCENODE_NONE;
		*pw_src_node_index = hr.u.m.src_node_index;
		*pw_dst_node_type = hr.u.m.dst_node_type + HPI_DESTNODE_NONE;
		*pw_dst_node_index = hr.u.m.dst_node_index;
	}
	if (pw_control_type)
		*pw_control_type = hr.u.m.control_index;

	if (ph_control) {
		if (hr.error == 0)
			*ph_control =
				hpi_indexes_to_handle(HPI_OBJ_CONTROL,
				hm.adapter_index, control_index);
		else
			*ph_control = 0;
	}
	return hr.error;
}