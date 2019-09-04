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
typedef  scalar_t__ u16 ;
struct hpi_response_header {int dummy; } ;
struct hpi_response {scalar_t__ error; int size; scalar_t__ specific_error; } ;
struct TYPE_5__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  pb_data; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_message {int function; TYPE_4__ u; } ;
struct hpi_adapter_obj {scalar_t__ dsp_crashed; } ;

/* Variables and functions */
 int /*<<< orphan*/  H620_HIF_GET_DATA ; 
 int /*<<< orphan*/  H620_HIF_SEND_DATA ; 
 scalar_t__ HPI_ERROR_BACKEND_BASE ; 
 scalar_t__ HPI_ERROR_DSP_COMMUNICATION ; 
#define  HPI_ISTREAM_ANC_WRITE 131 
#define  HPI_ISTREAM_READ 130 
#define  HPI_OSTREAM_ANC_READ 129 
#define  HPI_OSTREAM_WRITE 128 
 scalar_t__ hpi6205_transfer_data (struct hpi_adapter_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpios_dsplock_lock (struct hpi_adapter_obj*) ; 
 int /*<<< orphan*/  hpios_dsplock_unlock (struct hpi_adapter_obj*) ; 
 scalar_t__ message_response_sequence (struct hpi_adapter_obj*,struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static void hw_message(struct hpi_adapter_obj *pao, struct hpi_message *phm,
	struct hpi_response *phr)
{

	u16 err = 0;

	hpios_dsplock_lock(pao);

	err = message_response_sequence(pao, phm, phr);

	/* maybe an error response */
	if (err) {
		/* something failed in the HPI/DSP interface */
		if (err >= HPI_ERROR_BACKEND_BASE) {
			phr->error = HPI_ERROR_DSP_COMMUNICATION;
			phr->specific_error = err;
		} else {
			phr->error = err;
		}

		pao->dsp_crashed++;

		/* just the header of the response is valid */
		phr->size = sizeof(struct hpi_response_header);
		goto err;
	} else
		pao->dsp_crashed = 0;

	if (phr->error != 0)	/* something failed in the DSP */
		goto err;

	switch (phm->function) {
	case HPI_OSTREAM_WRITE:
	case HPI_ISTREAM_ANC_WRITE:
		err = hpi6205_transfer_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_SEND_DATA);
		break;

	case HPI_ISTREAM_READ:
	case HPI_OSTREAM_ANC_READ:
		err = hpi6205_transfer_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_GET_DATA);
		break;

	}
	phr->error = err;

err:
	hpios_dsplock_unlock(pao);

	return;
}