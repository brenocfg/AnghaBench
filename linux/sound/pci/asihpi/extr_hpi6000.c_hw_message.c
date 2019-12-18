#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct hpi_response_header {int dummy; } ;
struct TYPE_12__ {int dsp_index; int /*<<< orphan*/  count; } ;
struct TYPE_13__ {TYPE_5__ assert; } ;
struct TYPE_14__ {TYPE_6__ ax; } ;
struct hpi_response {int error; int specific_error; int size; TYPE_7__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  object_type; int /*<<< orphan*/  stream_index; } ;
struct TYPE_9__ {TYPE_1__ stream; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_11__ {TYPE_3__ d; } ;
struct hpi_message {int function; TYPE_4__ u; int /*<<< orphan*/  object; int /*<<< orphan*/  obj_index; } ;
struct hpi_hw_obj {int num_dsp; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;

/* Variables and functions */
#define  HPI_ADAPTER_GET_ASSERT 132 
 int HPI_ERROR_BACKEND_BASE ; 
 int HPI_ERROR_DSP_COMMUNICATION ; 
 int HPI_ERROR_NO_INTERDSP_GROUPS ; 
#define  HPI_ISTREAM_ANC_WRITE 131 
 int HPI_ISTREAM_GROUP_ADD ; 
#define  HPI_ISTREAM_READ 130 
#define  HPI_OSTREAM_ANC_READ 129 
 int HPI_OSTREAM_GROUP_ADD ; 
#define  HPI_OSTREAM_WRITE 128 
 int get_dsp_index (struct hpi_adapter_obj*,struct hpi_message*) ; 
 int hpi6000_get_data (struct hpi_adapter_obj*,int,struct hpi_message*,struct hpi_response*) ; 
 int hpi6000_message_response_sequence (struct hpi_adapter_obj*,int,struct hpi_message*,struct hpi_response*) ; 
 int hpi6000_send_data (struct hpi_adapter_obj*,int,struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  hpios_dsplock_lock (struct hpi_adapter_obj*) ; 
 int /*<<< orphan*/  hpios_dsplock_unlock (struct hpi_adapter_obj*) ; 

__attribute__((used)) static void hw_message(struct hpi_adapter_obj *pao, struct hpi_message *phm,
	struct hpi_response *phr)
{
	u16 error = 0;
	u16 dsp_index = 0;
	struct hpi_hw_obj *phw = pao->priv;
	u16 num_dsp = phw->num_dsp;

	if (num_dsp < 2)
		dsp_index = 0;
	else {
		dsp_index = get_dsp_index(pao, phm);

		/* is this  checked on the DSP anyway? */
		if ((phm->function == HPI_ISTREAM_GROUP_ADD)
			|| (phm->function == HPI_OSTREAM_GROUP_ADD)) {
			struct hpi_message hm;
			u16 add_index;
			hm.obj_index = phm->u.d.u.stream.stream_index;
			hm.object = phm->u.d.u.stream.object_type;
			add_index = get_dsp_index(pao, &hm);
			if (add_index != dsp_index) {
				phr->error = HPI_ERROR_NO_INTERDSP_GROUPS;
				return;
			}
		}
	}

	hpios_dsplock_lock(pao);
	error = hpi6000_message_response_sequence(pao, dsp_index, phm, phr);

	if (error)	/* something failed in the HPI/DSP interface */
		goto err;

	if (phr->error)	/* something failed in the DSP */
		goto out;

	switch (phm->function) {
	case HPI_OSTREAM_WRITE:
	case HPI_ISTREAM_ANC_WRITE:
		error = hpi6000_send_data(pao, dsp_index, phm, phr);
		break;
	case HPI_ISTREAM_READ:
	case HPI_OSTREAM_ANC_READ:
		error = hpi6000_get_data(pao, dsp_index, phm, phr);
		break;
	case HPI_ADAPTER_GET_ASSERT:
		phr->u.ax.assert.dsp_index = 0;	/* dsp 0 default */
		if (num_dsp == 2) {
			if (!phr->u.ax.assert.count) {
				/* no assert from dsp 0, check dsp 1 */
				error = hpi6000_message_response_sequence(pao,
					1, phm, phr);
				phr->u.ax.assert.dsp_index = 1;
			}
		}
	}

err:
	if (error) {
		if (error >= HPI_ERROR_BACKEND_BASE) {
			phr->error = HPI_ERROR_DSP_COMMUNICATION;
			phr->specific_error = error;
		} else {
			phr->error = error;
		}

		/* just the header of the response is valid */
		phr->size = sizeof(struct hpi_response_header);
	}
out:
	hpios_dsplock_unlock(pao);
	return;
}