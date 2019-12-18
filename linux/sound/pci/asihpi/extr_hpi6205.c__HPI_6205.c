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
struct hpi_response {int /*<<< orphan*/  error; } ;
struct hpi_message {scalar_t__ function; int type; int /*<<< orphan*/  object; } ;
struct hpi_adapter_obj {int dsp_crashed; } ;

/* Variables and functions */
 scalar_t__ HPI_ADAPTER_DEBUG_READ ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  HPI_ERROR_DSP_HARDWARE ; 
 int /*<<< orphan*/  HPI_ERROR_INVALID_TYPE ; 
 int /*<<< orphan*/  HPI_ERROR_PROCESSING_MESSAGE ; 
#define  HPI_OBJ_ADAPTER 133 
#define  HPI_OBJ_CONTROL 132 
#define  HPI_OBJ_ISTREAM 131 
#define  HPI_OBJ_OSTREAM 130 
#define  HPI_OBJ_SUBSYSTEM 129 
 scalar_t__ HPI_SUBSYS_CREATE_ADAPTER ; 
#define  HPI_TYPE_REQUEST 128 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  adapter_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  control_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  instream_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  outstream_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  subsys_message (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static
void _HPI_6205(struct hpi_adapter_obj *pao, struct hpi_message *phm,
	struct hpi_response *phr)
{
	if (pao && (pao->dsp_crashed >= 10)
		&& (phm->function != HPI_ADAPTER_DEBUG_READ)) {
		/* allow last resort debug read even after crash */
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_DSP_HARDWARE);
		HPI_DEBUG_LOG(WARNING, " %d,%d dsp crashed.\n", phm->object,
			phm->function);
		return;
	}

	/* Init default response  */
	if (phm->function != HPI_SUBSYS_CREATE_ADAPTER)
		phr->error = HPI_ERROR_PROCESSING_MESSAGE;

	HPI_DEBUG_LOG(VERBOSE, "start of switch\n");
	switch (phm->type) {
	case HPI_TYPE_REQUEST:
		switch (phm->object) {
		case HPI_OBJ_SUBSYSTEM:
			subsys_message(pao, phm, phr);
			break;

		case HPI_OBJ_ADAPTER:
			adapter_message(pao, phm, phr);
			break;

		case HPI_OBJ_CONTROL:
			control_message(pao, phm, phr);
			break;

		case HPI_OBJ_OSTREAM:
			outstream_message(pao, phm, phr);
			break;

		case HPI_OBJ_ISTREAM:
			instream_message(pao, phm, phr);
			break;

		default:
			hw_message(pao, phm, phr);
			break;
		}
		break;

	default:
		phr->error = HPI_ERROR_INVALID_TYPE;
		break;
	}
}