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
struct hpi_response {scalar_t__ error; } ;
struct hpi_message {scalar_t__ type; int object; scalar_t__ adapter_index; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 scalar_t__ HPIMSGX_ALLADAPTERS ; 
 int /*<<< orphan*/  HPI_DEBUG_LEVEL_ERROR ; 
 int /*<<< orphan*/  HPI_DEBUG_MESSAGE (int /*<<< orphan*/ ,struct hpi_message*) ; 
 int /*<<< orphan*/  HPI_DEBUG_RESPONSE (struct hpi_response*) ; 
 int /*<<< orphan*/  HPI_ERROR_BAD_ADAPTER_NUMBER ; 
 scalar_t__ HPI_ERROR_DSP_COMMUNICATION ; 
 int /*<<< orphan*/  HPI_ERROR_INVALID_TYPE ; 
 scalar_t__ HPI_MAX_ADAPTERS ; 
#define  HPI_OBJ_ADAPTER 132 
#define  HPI_OBJ_ISTREAM 131 
#define  HPI_OBJ_MIXER 130 
#define  HPI_OBJ_OSTREAM 129 
#define  HPI_OBJ_SUBSYSTEM 128 
 scalar_t__ HPI_TYPE_REQUEST ; 
 int /*<<< orphan*/  adapter_message (struct hpi_message*,struct hpi_response*,void*) ; 
 int /*<<< orphan*/  hpi_debug_level_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_entry_point (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_message (struct hpi_message*,struct hpi_response*,void*) ; 
 scalar_t__ logging_enabled ; 
 int /*<<< orphan*/  mixer_message (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_message (struct hpi_message*,struct hpi_response*,void*) ; 
 int /*<<< orphan*/  subsys_message (struct hpi_message*,struct hpi_response*,void*) ; 

void hpi_send_recv_ex(struct hpi_message *phm, struct hpi_response *phr,
	void *h_owner)
{

	if (logging_enabled)
		HPI_DEBUG_MESSAGE(DEBUG, phm);

	if (phm->type != HPI_TYPE_REQUEST) {
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_INVALID_TYPE);
		return;
	}

	if (phm->adapter_index >= HPI_MAX_ADAPTERS
		&& phm->adapter_index != HPIMSGX_ALLADAPTERS) {
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_BAD_ADAPTER_NUMBER);
		return;
	}

	switch (phm->object) {
	case HPI_OBJ_SUBSYSTEM:
		subsys_message(phm, phr, h_owner);
		break;

	case HPI_OBJ_ADAPTER:
		adapter_message(phm, phr, h_owner);
		break;

	case HPI_OBJ_MIXER:
		mixer_message(phm, phr);
		break;

	case HPI_OBJ_OSTREAM:
		outstream_message(phm, phr, h_owner);
		break;

	case HPI_OBJ_ISTREAM:
		instream_message(phm, phr, h_owner);
		break;

	default:
		hw_entry_point(phm, phr);
		break;
	}

	if (logging_enabled)
		HPI_DEBUG_RESPONSE(phr);

	if (phr->error >= HPI_ERROR_DSP_COMMUNICATION) {
		hpi_debug_level_set(HPI_DEBUG_LEVEL_ERROR);
		logging_enabled = 0;
	}
}