#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hpi_response_header {int dummy; } ;
struct hpi_response {int specific_error; int size; int /*<<< orphan*/  error; } ;
struct TYPE_3__ {int size; } ;
struct hpi_message {int size; scalar_t__ function; TYPE_1__ response; } ;
struct hpi_hw_obj {struct bus_master_interface* p_interface_buffer; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;
struct TYPE_4__ {struct hpi_message response_buffer; struct hpi_response message_buffer; } ;
struct bus_master_interface {TYPE_2__ u; int /*<<< orphan*/  dsp_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  H620_HIF_GET_RESP ; 
 int /*<<< orphan*/  H620_HIF_IDLE ; 
 int /*<<< orphan*/  HPI6205_ERROR_MSG_RESP_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  HPI6205_ERROR_MSG_RESP_TIMEOUT ; 
 scalar_t__ HPI6205_TIMEOUT ; 
 scalar_t__ HPI_ADAPTER_CLOSE ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  HPI_ERROR_MESSAGE_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  hpi_validate_response (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  memcpy (struct hpi_response*,struct hpi_message*,int) ; 
 int /*<<< orphan*/  message_count ; 
 int /*<<< orphan*/  send_dsp_command (struct hpi_hw_obj*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_dsp_ack (struct hpi_hw_obj*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u16 message_response_sequence(struct hpi_adapter_obj *pao,
	struct hpi_message *phm, struct hpi_response *phr)
{
	u32 time_out, time_out2;
	struct hpi_hw_obj *phw = pao->priv;
	struct bus_master_interface *interface = phw->p_interface_buffer;
	u16 err = 0;

	message_count++;
	if (phm->size > sizeof(interface->u.message_buffer)) {
		phr->error = HPI_ERROR_MESSAGE_BUFFER_TOO_SMALL;
		phr->specific_error = sizeof(interface->u.message_buffer);
		phr->size = sizeof(struct hpi_response_header);
		HPI_DEBUG_LOG(ERROR,
			"message len %d too big for buffer %zd \n", phm->size,
			sizeof(interface->u.message_buffer));
		return 0;
	}

	/* Assume buffer of type struct bus_master_interface_62
	   is allocated "noncacheable" */

	if (!wait_dsp_ack(phw, H620_HIF_IDLE, HPI6205_TIMEOUT)) {
		HPI_DEBUG_LOG(DEBUG, "timeout waiting for idle\n");
		return HPI6205_ERROR_MSG_RESP_IDLE_TIMEOUT;
	}

	memcpy(&interface->u.message_buffer, phm, phm->size);
	/* signal we want a response */
	send_dsp_command(phw, H620_HIF_GET_RESP);

	time_out2 = wait_dsp_ack(phw, H620_HIF_GET_RESP, HPI6205_TIMEOUT);

	if (!time_out2) {
		HPI_DEBUG_LOG(ERROR,
			"(%u) Timed out waiting for " "GET_RESP state [%x]\n",
			message_count, interface->dsp_ack);
	} else {
		HPI_DEBUG_LOG(VERBOSE,
			"(%u) transition to GET_RESP after %u\n",
			message_count, HPI6205_TIMEOUT - time_out2);
	}
	/* spin waiting on HIF interrupt flag (end of msg process) */
	time_out = HPI6205_TIMEOUT;

	/* read the result */
	if (time_out) {
		if (interface->u.response_buffer.response.size <= phr->size)
			memcpy(phr, &interface->u.response_buffer,
				interface->u.response_buffer.response.size);
		else {
			HPI_DEBUG_LOG(ERROR,
				"response len %d too big for buffer %d\n",
				interface->u.response_buffer.response.size,
				phr->size);
			memcpy(phr, &interface->u.response_buffer,
				sizeof(struct hpi_response_header));
			phr->error = HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;
			phr->specific_error =
				interface->u.response_buffer.response.size;
			phr->size = sizeof(struct hpi_response_header);
		}
	}
	/* set interface back to idle */
	send_dsp_command(phw, H620_HIF_IDLE);

	if (!time_out || !time_out2) {
		HPI_DEBUG_LOG(DEBUG, "something timed out!\n");
		return HPI6205_ERROR_MSG_RESP_TIMEOUT;
	}
	/* special case for adapter close - */
	/* wait for the DSP to indicate it is idle */
	if (phm->function == HPI_ADAPTER_CLOSE) {
		if (!wait_dsp_ack(phw, H620_HIF_IDLE, HPI6205_TIMEOUT)) {
			HPI_DEBUG_LOG(DEBUG,
				"Timeout waiting for idle "
				"(on adapter_close)\n");
			return HPI6205_ERROR_MSG_RESP_IDLE_TIMEOUT;
		}
	}
	err = hpi_validate_response(phm, phr);
	return err;
}