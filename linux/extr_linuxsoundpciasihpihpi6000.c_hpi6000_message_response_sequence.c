#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct hpi_response {scalar_t__ size; } ;
struct hpi_message {scalar_t__ size; } ;
struct hpi_hw_obj {scalar_t__ message_buffer_address_on_dsp; scalar_t__ response_buffer_address_on_dsp; struct dsp_obj* ado; } ;
struct hpi_adapter_obj {scalar_t__ dsp_crashed; struct hpi_hw_obj* priv; } ;
struct dsp_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H6READ ; 
 short HPI6000_ERROR_MSG_GET_ADR ; 
 short HPI6000_ERROR_MSG_RESP_BLOCKREAD32 ; 
 short HPI6000_ERROR_MSG_RESP_BLOCKWRITE32 ; 
 short HPI6000_ERROR_MSG_RESP_GETRESPCMD ; 
 short HPI6000_ERROR_MSG_RESP_GET_RESP_ACK ; 
 short HPI6000_ERROR_MSG_RESP_IDLECMD ; 
 short HPI6000_ERROR_MSG_RESP_IDLE_TIMEOUT ; 
 short HPI6000_ERROR_RESP_GET_ADR ; 
 short HPI6000_ERROR_RESP_GET_LEN ; 
 short HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  HPI_HIF_ADDR (scalar_t__) ; 
 size_t HPI_HIF_ERROR_MASK ; 
 int /*<<< orphan*/  HPI_HIF_GET_RESP ; 
 int /*<<< orphan*/  HPI_HIF_IDLE ; 
 scalar_t__ TIMEOUT ; 
 scalar_t__ hpi6000_check_PCI2040_error_flag (struct hpi_adapter_obj*,int /*<<< orphan*/ ) ; 
 scalar_t__ hpi6000_dsp_block_read32 (struct hpi_adapter_obj*,size_t,scalar_t__,scalar_t__*,size_t) ; 
 scalar_t__ hpi6000_dsp_block_write32 (struct hpi_adapter_obj*,size_t,scalar_t__,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  hpi6000_send_dsp_interrupt (struct dsp_obj*) ; 
 scalar_t__ hpi6000_send_host_command (struct hpi_adapter_obj*,size_t,int /*<<< orphan*/ ) ; 
 size_t hpi6000_wait_dsp_ack (struct hpi_adapter_obj*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ hpi_read_word (struct dsp_obj*,int /*<<< orphan*/ ) ; 
 size_t hpi_validate_response (struct hpi_message*,struct hpi_response*) ; 
 scalar_t__ message_buffer_address ; 
 scalar_t__ response_buffer_address ; 

__attribute__((used)) static short hpi6000_message_response_sequence(struct hpi_adapter_obj *pao,
	u16 dsp_index, struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 timeout;
	u16 ack;
	u32 address;
	u32 length;
	u32 *p_data;
	u16 error = 0;

	ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_IDLE);
	if (ack & HPI_HIF_ERROR_MASK) {
		pao->dsp_crashed++;
		return HPI6000_ERROR_MSG_RESP_IDLE_TIMEOUT;
	}
	pao->dsp_crashed = 0;

	/* get the message address and size */
	if (phw->message_buffer_address_on_dsp == 0) {
		timeout = TIMEOUT;
		do {
			address =
				hpi_read_word(pdo,
				HPI_HIF_ADDR(message_buffer_address));
			phw->message_buffer_address_on_dsp = address;
		} while (hpi6000_check_PCI2040_error_flag(pao, H6READ)
			&& --timeout);
		if (!timeout)
			return HPI6000_ERROR_MSG_GET_ADR;
	} else
		address = phw->message_buffer_address_on_dsp;

	length = phm->size;

	/* send the message */
	p_data = (u32 *)phm;
	if (hpi6000_dsp_block_write32(pao, dsp_index, address, p_data,
			(u16)length / 4))
		return HPI6000_ERROR_MSG_RESP_BLOCKWRITE32;

	if (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_GET_RESP))
		return HPI6000_ERROR_MSG_RESP_GETRESPCMD;
	hpi6000_send_dsp_interrupt(pdo);

	ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_GET_RESP);
	if (ack & HPI_HIF_ERROR_MASK)
		return HPI6000_ERROR_MSG_RESP_GET_RESP_ACK;

	/* get the response address */
	if (phw->response_buffer_address_on_dsp == 0) {
		timeout = TIMEOUT;
		do {
			address =
				hpi_read_word(pdo,
				HPI_HIF_ADDR(response_buffer_address));
		} while (hpi6000_check_PCI2040_error_flag(pao, H6READ)
			&& --timeout);
		phw->response_buffer_address_on_dsp = address;

		if (!timeout)
			return HPI6000_ERROR_RESP_GET_ADR;
	} else
		address = phw->response_buffer_address_on_dsp;

	/* read the length of the response back from the DSP */
	timeout = TIMEOUT;
	do {
		length = hpi_read_word(pdo, HPI_HIF_ADDR(length));
	} while (hpi6000_check_PCI2040_error_flag(pao, H6READ) && --timeout);
	if (!timeout)
		return HPI6000_ERROR_RESP_GET_LEN;

	if (length > phr->size)
		return HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;

	/* get the response */
	p_data = (u32 *)phr;
	if (hpi6000_dsp_block_read32(pao, dsp_index, address, p_data,
			(u16)length / 4))
		return HPI6000_ERROR_MSG_RESP_BLOCKREAD32;

	/* set i/f back to idle */
	if (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDLE))
		return HPI6000_ERROR_MSG_RESP_IDLECMD;
	hpi6000_send_dsp_interrupt(pdo);

	error = hpi_validate_response(phm, phr);
	return error;
}