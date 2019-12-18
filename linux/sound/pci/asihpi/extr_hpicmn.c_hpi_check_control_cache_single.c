#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct hpi_response_header {int dummy; } ;
struct TYPE_29__ {unsigned int remaining_chars; int /*<<< orphan*/  sz_data; } ;
struct TYPE_42__ {void* s_level; } ;
struct TYPE_30__ {TYPE_15__ chars8; TYPE_6__ tuner; } ;
struct TYPE_28__ {int /*<<< orphan*/  param1; void** an_log_value; int /*<<< orphan*/  param2; } ;
struct TYPE_31__ {TYPE_16__ cu; TYPE_14__ c; } ;
struct hpi_response {int /*<<< orphan*/  function; int /*<<< orphan*/  object; int /*<<< orphan*/  type; scalar_t__ size; TYPE_17__ u; void* error; } ;
struct TYPE_35__ {unsigned int param1; int /*<<< orphan*/  attribute; } ;
struct TYPE_36__ {TYPE_20__ c; } ;
struct hpi_message {int /*<<< orphan*/  function; int /*<<< orphan*/  object; TYPE_21__ u; int /*<<< orphan*/  adapter_index; } ;
struct hpi_control_res {int dummy; } ;
struct TYPE_32__ {int /*<<< orphan*/  control_type; int /*<<< orphan*/  control_index; } ;
struct TYPE_27__ {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  source_index; int /*<<< orphan*/  source; } ;
struct TYPE_26__ {int /*<<< orphan*/  phantom_state; } ;
struct TYPE_25__ {int /*<<< orphan*/  state; } ;
struct TYPE_24__ {int /*<<< orphan*/  state; } ;
struct TYPE_45__ {int /*<<< orphan*/  format; } ;
struct TYPE_44__ {int /*<<< orphan*/  format; int /*<<< orphan*/  error_status; } ;
struct TYPE_43__ {void* s_level_avg; int /*<<< orphan*/  band; int /*<<< orphan*/  freq_ink_hz; } ;
struct TYPE_41__ {void** an_log; } ;
struct TYPE_40__ {int /*<<< orphan*/  mode; } ;
struct TYPE_39__ {int /*<<< orphan*/  source_node_index; int /*<<< orphan*/  source_node_type; } ;
struct TYPE_38__ {int flags; void** an_log; } ;
struct TYPE_34__ {void** an_logRMS; void** an_log_peak; } ;
struct TYPE_33__ {TYPE_18__ i; TYPE_13__ clk; TYPE_12__ microphone; TYPE_11__ silence; TYPE_10__ tone; TYPE_9__ aes3tx; TYPE_8__ aes3rx; TYPE_7__ tuner; TYPE_5__ level; TYPE_4__ mode; TYPE_3__ mux; TYPE_2__ vol; TYPE_1__ meter; } ;
struct hpi_control_cache_single {TYPE_19__ u; } ;
struct hpi_control_cache_pad {int field_valid_flags; int /*<<< orphan*/  pTY; int /*<<< orphan*/  pI; } ;
struct TYPE_37__ {int offset; unsigned int field_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_22__*) ; 
 int /*<<< orphan*/  HPI_AESEBURX_ERRORSTATUS ; 
 int /*<<< orphan*/  HPI_AESEBURX_FORMAT ; 
 int /*<<< orphan*/  HPI_AESEBUTX_FORMAT ; 
 int /*<<< orphan*/  HPI_BITMASK_ALL_CHANNELS ; 
 void* HPI_CACHE_INVALID_SHORT ; 
 int /*<<< orphan*/  HPI_CACHE_INVALID_UINT16 ; 
 int /*<<< orphan*/  HPI_CHANNEL_MODE_MODE ; 
#define  HPI_CONTROL_AESEBU_RECEIVER 140 
#define  HPI_CONTROL_AESEBU_TRANSMITTER 139 
#define  HPI_CONTROL_CHANNEL_MODE 138 
#define  HPI_CONTROL_LEVEL 137 
#define  HPI_CONTROL_METER 136 
#define  HPI_CONTROL_MICROPHONE 135 
#define  HPI_CONTROL_MULTIPLEXER 134 
#define  HPI_CONTROL_PAD 133 
#define  HPI_CONTROL_SAMPLECLOCK 132 
#define  HPI_CONTROL_SILENCEDETECTOR 131 
#define  HPI_CONTROL_TONEDETECTOR 130 
#define  HPI_CONTROL_TUNER 129 
#define  HPI_CONTROL_VOLUME 128 
 int HPI_CTL_ATTR_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* HPI_ERROR_INVALID_CONTROL_ATTRIBUTE ; 
 void* HPI_ERROR_INVALID_CONTROL_VALUE ; 
 int /*<<< orphan*/  HPI_LEVEL_GAIN ; 
 void* HPI_METER_MINIMUM ; 
 int /*<<< orphan*/  HPI_METER_PEAK ; 
 int /*<<< orphan*/  HPI_METER_RMS ; 
 int /*<<< orphan*/  HPI_MICROPHONE_PHANTOM_POWER ; 
 int /*<<< orphan*/  HPI_MULTIPLEXER_SOURCE ; 
 int /*<<< orphan*/  HPI_PAD_PROGRAM_ID ; 
 int /*<<< orphan*/  HPI_PAD_PROGRAM_TYPE ; 
 int /*<<< orphan*/  HPI_SAMPLECLOCK_SAMPLERATE ; 
 int /*<<< orphan*/  HPI_SAMPLECLOCK_SOURCE ; 
 int /*<<< orphan*/  HPI_SAMPLECLOCK_SOURCE_INDEX ; 
 int /*<<< orphan*/  HPI_SILENCEDETECTOR_STATE ; 
 int /*<<< orphan*/  HPI_TONEDETECTOR_STATE ; 
 int /*<<< orphan*/  HPI_TUNER_BAND ; 
 int /*<<< orphan*/  HPI_TUNER_FREQ ; 
 int /*<<< orphan*/  HPI_TUNER_LEVEL_AVG ; 
 int /*<<< orphan*/  HPI_TYPE_RESPONSE ; 
 int HPI_VOLUME_FLAG_HAS_MUTE ; 
 int HPI_VOLUME_FLAG_MUTED ; 
 int /*<<< orphan*/  HPI_VOLUME_GAIN ; 
 int /*<<< orphan*/  HPI_VOLUME_MUTE ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,unsigned int) ; 
 TYPE_22__* pad_desc ; 
 int /*<<< orphan*/  strlen (char*) ; 

short hpi_check_control_cache_single(struct hpi_control_cache_single *pC,
	struct hpi_message *phm, struct hpi_response *phr)
{
	size_t response_size;
	short found = 1;

	/* set the default response size */
	response_size =
		sizeof(struct hpi_response_header) +
		sizeof(struct hpi_control_res);

	switch (pC->u.i.control_type) {

	case HPI_CONTROL_METER:
		if (phm->u.c.attribute == HPI_METER_PEAK) {
			phr->u.c.an_log_value[0] = pC->u.meter.an_log_peak[0];
			phr->u.c.an_log_value[1] = pC->u.meter.an_log_peak[1];
		} else if (phm->u.c.attribute == HPI_METER_RMS) {
			if (pC->u.meter.an_logRMS[0] ==
				HPI_CACHE_INVALID_SHORT) {
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
				phr->u.c.an_log_value[0] = HPI_METER_MINIMUM;
				phr->u.c.an_log_value[1] = HPI_METER_MINIMUM;
			} else {
				phr->u.c.an_log_value[0] =
					pC->u.meter.an_logRMS[0];
				phr->u.c.an_log_value[1] =
					pC->u.meter.an_logRMS[1];
			}
		} else
			found = 0;
		break;
	case HPI_CONTROL_VOLUME:
		if (phm->u.c.attribute == HPI_VOLUME_GAIN) {
			phr->u.c.an_log_value[0] = pC->u.vol.an_log[0];
			phr->u.c.an_log_value[1] = pC->u.vol.an_log[1];
		} else if (phm->u.c.attribute == HPI_VOLUME_MUTE) {
			if (pC->u.vol.flags & HPI_VOLUME_FLAG_HAS_MUTE) {
				if (pC->u.vol.flags & HPI_VOLUME_FLAG_MUTED)
					phr->u.c.param1 =
						HPI_BITMASK_ALL_CHANNELS;
				else
					phr->u.c.param1 = 0;
			} else {
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
				phr->u.c.param1 = 0;
			}
		} else {
			found = 0;
		}
		break;
	case HPI_CONTROL_MULTIPLEXER:
		if (phm->u.c.attribute == HPI_MULTIPLEXER_SOURCE) {
			phr->u.c.param1 = pC->u.mux.source_node_type;
			phr->u.c.param2 = pC->u.mux.source_node_index;
		} else {
			found = 0;
		}
		break;
	case HPI_CONTROL_CHANNEL_MODE:
		if (phm->u.c.attribute == HPI_CHANNEL_MODE_MODE)
			phr->u.c.param1 = pC->u.mode.mode;
		else
			found = 0;
		break;
	case HPI_CONTROL_LEVEL:
		if (phm->u.c.attribute == HPI_LEVEL_GAIN) {
			phr->u.c.an_log_value[0] = pC->u.level.an_log[0];
			phr->u.c.an_log_value[1] = pC->u.level.an_log[1];
		} else
			found = 0;
		break;
	case HPI_CONTROL_TUNER:
		if (phm->u.c.attribute == HPI_TUNER_FREQ)
			phr->u.c.param1 = pC->u.tuner.freq_ink_hz;
		else if (phm->u.c.attribute == HPI_TUNER_BAND)
			phr->u.c.param1 = pC->u.tuner.band;
		else if (phm->u.c.attribute == HPI_TUNER_LEVEL_AVG)
			if (pC->u.tuner.s_level_avg ==
				HPI_CACHE_INVALID_SHORT) {
				phr->u.cu.tuner.s_level = 0;
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
			} else
				phr->u.cu.tuner.s_level =
					pC->u.tuner.s_level_avg;
		else
			found = 0;
		break;
	case HPI_CONTROL_AESEBU_RECEIVER:
		if (phm->u.c.attribute == HPI_AESEBURX_ERRORSTATUS)
			phr->u.c.param1 = pC->u.aes3rx.error_status;
		else if (phm->u.c.attribute == HPI_AESEBURX_FORMAT)
			phr->u.c.param1 = pC->u.aes3rx.format;
		else
			found = 0;
		break;
	case HPI_CONTROL_AESEBU_TRANSMITTER:
		if (phm->u.c.attribute == HPI_AESEBUTX_FORMAT)
			phr->u.c.param1 = pC->u.aes3tx.format;
		else
			found = 0;
		break;
	case HPI_CONTROL_TONEDETECTOR:
		if (phm->u.c.attribute == HPI_TONEDETECTOR_STATE)
			phr->u.c.param1 = pC->u.tone.state;
		else
			found = 0;
		break;
	case HPI_CONTROL_SILENCEDETECTOR:
		if (phm->u.c.attribute == HPI_SILENCEDETECTOR_STATE) {
			phr->u.c.param1 = pC->u.silence.state;
		} else
			found = 0;
		break;
	case HPI_CONTROL_MICROPHONE:
		if (phm->u.c.attribute == HPI_MICROPHONE_PHANTOM_POWER)
			phr->u.c.param1 = pC->u.microphone.phantom_state;
		else
			found = 0;
		break;
	case HPI_CONTROL_SAMPLECLOCK:
		if (phm->u.c.attribute == HPI_SAMPLECLOCK_SOURCE)
			phr->u.c.param1 = pC->u.clk.source;
		else if (phm->u.c.attribute == HPI_SAMPLECLOCK_SOURCE_INDEX) {
			if (pC->u.clk.source_index ==
				HPI_CACHE_INVALID_UINT16) {
				phr->u.c.param1 = 0;
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
			} else
				phr->u.c.param1 = pC->u.clk.source_index;
		} else if (phm->u.c.attribute == HPI_SAMPLECLOCK_SAMPLERATE)
			phr->u.c.param1 = pC->u.clk.sample_rate;
		else
			found = 0;
		break;
	case HPI_CONTROL_PAD:{
			struct hpi_control_cache_pad *p_pad;
			p_pad = (struct hpi_control_cache_pad *)pC;

			if (!(p_pad->field_valid_flags & (1 <<
						HPI_CTL_ATTR_INDEX(phm->u.c.
							attribute)))) {
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
				break;
			}

			if (phm->u.c.attribute == HPI_PAD_PROGRAM_ID)
				phr->u.c.param1 = p_pad->pI;
			else if (phm->u.c.attribute == HPI_PAD_PROGRAM_TYPE)
				phr->u.c.param1 = p_pad->pTY;
			else {
				unsigned int index =
					HPI_CTL_ATTR_INDEX(phm->u.c.
					attribute) - 1;
				unsigned int offset = phm->u.c.param1;
				unsigned int pad_string_len, field_size;
				char *pad_string;
				unsigned int tocopy;

				if (index > ARRAY_SIZE(pad_desc) - 1) {
					phr->error =
						HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
					break;
				}

				pad_string =
					((char *)p_pad) +
					pad_desc[index].offset;
				field_size = pad_desc[index].field_size;
				/* Ensure null terminator */
				pad_string[field_size - 1] = 0;

				pad_string_len = strlen(pad_string) + 1;

				if (offset > pad_string_len) {
					phr->error =
						HPI_ERROR_INVALID_CONTROL_VALUE;
					break;
				}

				tocopy = pad_string_len - offset;
				if (tocopy > sizeof(phr->u.cu.chars8.sz_data))
					tocopy = sizeof(phr->u.cu.chars8.
						sz_data);

				memcpy(phr->u.cu.chars8.sz_data,
					&pad_string[offset], tocopy);

				phr->u.cu.chars8.remaining_chars =
					pad_string_len - offset - tocopy;
			}
		}
		break;
	default:
		found = 0;
		break;
	}

	HPI_DEBUG_LOG(VERBOSE, "%s Adap %d, Ctl %d, Type %d, Attr %d\n",
		found ? "Cached" : "Uncached", phm->adapter_index,
		pC->u.i.control_index, pC->u.i.control_type,
		phm->u.c.attribute);

	if (found) {
		phr->size = (u16)response_size;
		phr->type = HPI_TYPE_RESPONSE;
		phr->object = phm->object;
		phr->function = phm->function;
	}

	return found;
}