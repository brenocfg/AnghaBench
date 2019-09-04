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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_9__ {int /*<<< orphan*/  oq_ci_offset; } ;
struct TYPE_10__ {TYPE_4__ create_operational_oq; } ;
struct pqi_general_admin_response {TYPE_5__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  int_msg_num; int /*<<< orphan*/  queue_protocol; int /*<<< orphan*/  element_length; int /*<<< orphan*/  num_elements; int /*<<< orphan*/  pi_addr; int /*<<< orphan*/  element_array_addr; int /*<<< orphan*/  queue_id; } ;
struct TYPE_8__ {TYPE_2__ create_operational_oq; } ;
struct TYPE_6__ {int /*<<< orphan*/  iu_length; int /*<<< orphan*/  iu_type; } ;
struct pqi_general_admin_request {TYPE_3__ data; int /*<<< orphan*/  function_code; TYPE_1__ header; } ;
struct pqi_event_queue {int oq_id; int int_msg_num; scalar_t__ oq_ci; scalar_t__ oq_pi_bus_addr; scalar_t__ oq_element_array_bus_addr; } ;
struct pqi_ctrl_info {scalar_t__ iomem_base; struct pqi_event_queue event_queue; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 scalar_t__ PQI_DEVICE_REGISTERS_OFFSET ; 
 int PQI_EVENT_OQ_ELEMENT_LENGTH ; 
 int /*<<< orphan*/  PQI_GENERAL_ADMIN_FUNCTION_CREATE_OQ ; 
 int PQI_GENERAL_ADMIN_IU_LENGTH ; 
 int PQI_NUM_EVENT_QUEUE_ELEMENTS ; 
 int /*<<< orphan*/  PQI_PROTOCOL_SOP ; 
 int /*<<< orphan*/  PQI_REQUEST_IU_GENERAL_ADMIN ; 
 scalar_t__ get_unaligned_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct pqi_general_admin_request*,int /*<<< orphan*/ ,int) ; 
 int pqi_submit_admin_request_synchronous (struct pqi_ctrl_info*,struct pqi_general_admin_request*,struct pqi_general_admin_response*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqi_create_event_queue(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	struct pqi_event_queue *event_queue;
	struct pqi_general_admin_request request;
	struct pqi_general_admin_response response;

	event_queue = &ctrl_info->event_queue;

	/*
	 * Create OQ (Outbound Queue - device to host queue) to dedicate
	 * to events.
	 */
	memset(&request, 0, sizeof(request));
	request.header.iu_type = PQI_REQUEST_IU_GENERAL_ADMIN;
	put_unaligned_le16(PQI_GENERAL_ADMIN_IU_LENGTH,
		&request.header.iu_length);
	request.function_code = PQI_GENERAL_ADMIN_FUNCTION_CREATE_OQ;
	put_unaligned_le16(event_queue->oq_id,
		&request.data.create_operational_oq.queue_id);
	put_unaligned_le64((u64)event_queue->oq_element_array_bus_addr,
		&request.data.create_operational_oq.element_array_addr);
	put_unaligned_le64((u64)event_queue->oq_pi_bus_addr,
		&request.data.create_operational_oq.pi_addr);
	put_unaligned_le16(PQI_NUM_EVENT_QUEUE_ELEMENTS,
		&request.data.create_operational_oq.num_elements);
	put_unaligned_le16(PQI_EVENT_OQ_ELEMENT_LENGTH / 16,
		&request.data.create_operational_oq.element_length);
	request.data.create_operational_oq.queue_protocol = PQI_PROTOCOL_SOP;
	put_unaligned_le16(event_queue->int_msg_num,
		&request.data.create_operational_oq.int_msg_num);

	rc = pqi_submit_admin_request_synchronous(ctrl_info, &request,
		&response);
	if (rc)
		return rc;

	event_queue->oq_ci = ctrl_info->iomem_base +
		PQI_DEVICE_REGISTERS_OFFSET +
		get_unaligned_le64(
			&response.data.create_operational_oq.oq_ci_offset);

	return 0;
}