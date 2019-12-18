#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct encoder_packet {scalar_t__ size; int timebase_num; int /*<<< orphan*/  timebase_den; int /*<<< orphan*/  type; void* data; void* dts; void* pts; } ;
struct encoder_frame {void** data; } ;
struct TYPE_10__ {int frameLength; void* encoderDelay; void* nDelay; } ;
struct TYPE_11__ {int frame_size_bytes; int channels; int packet_buffer_size; void* total_samples; int /*<<< orphan*/  sample_rate; void* packet_buffer; TYPE_1__ info; int /*<<< orphan*/  fdkhandle; } ;
typedef  TYPE_2__ libfdk_encoder_t ;
typedef  void* int64_t ;
struct TYPE_14__ {int numBufs; void** bufs; int* bufferIdentifiers; int* bufSizes; int* bufElSizes; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int numInSamples; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {scalar_t__ numOutBytes; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ AACENC_OutArgs ;
typedef  TYPE_4__ AACENC_InArgs ;
typedef  int /*<<< orphan*/  AACENC_ERROR ;
typedef  TYPE_5__ AACENC_BufDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AACENC_OK ; 
 int IN_AUDIO_DATA ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  OBS_ENCODER_AUDIO ; 
 int OUT_BITSTREAM_DATA ; 
 int /*<<< orphan*/  aacEncEncode (int /*<<< orphan*/ ,TYPE_5__*,TYPE_5__*,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libfdk_get_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool libfdk_encode(void *data, struct encoder_frame *frame,
			  struct encoder_packet *packet, bool *received_packet)
{
	libfdk_encoder_t *enc = data;

	AACENC_BufDesc in_buf = {0};
	AACENC_BufDesc out_buf = {0};
	AACENC_InArgs in_args = {0};
	AACENC_OutArgs out_args = {0};
	int in_identifier = IN_AUDIO_DATA;
	int in_size, in_elem_size;
	int out_identifier = OUT_BITSTREAM_DATA;
	int out_size, out_elem_size;
	void *in_ptr;
	void *out_ptr;
	AACENC_ERROR err;
	int64_t encoderDelay;

	in_ptr = frame->data[0];
	in_size = enc->frame_size_bytes;
	in_elem_size = 2;

	in_args.numInSamples = enc->info.frameLength * enc->channels;
	in_buf.numBufs = 1;
	in_buf.bufs = &in_ptr;
	in_buf.bufferIdentifiers = &in_identifier;
	in_buf.bufSizes = &in_size;
	in_buf.bufElSizes = &in_elem_size;

	out_ptr = enc->packet_buffer;
	out_size = enc->packet_buffer_size;
	out_elem_size = 1;

	out_buf.numBufs = 1;
	out_buf.bufs = &out_ptr;
	out_buf.bufferIdentifiers = &out_identifier;
	out_buf.bufSizes = &out_size;
	out_buf.bufElSizes = &out_elem_size;

	if ((err = aacEncEncode(enc->fdkhandle, &in_buf, &out_buf, &in_args,
				&out_args)) != AACENC_OK) {
		blog(LOG_ERROR, "Failed to encode frame: %s",
		     libfdk_get_error(err));
		return false;
	}

	enc->total_samples += enc->info.frameLength;

	if (out_args.numOutBytes == 0) {
		*received_packet = false;
		return true;
	}

	*received_packet = true;
#if (AACENCODER_LIB_VL0 >= 4)
	encoderDelay = enc->info.nDelay;
#else
	encoderDelay = enc->info.encoderDelay;
#endif
	packet->pts = enc->total_samples - encoderDelay;
	packet->dts = enc->total_samples - encoderDelay;
	packet->data = enc->packet_buffer;
	packet->size = out_args.numOutBytes;
	packet->type = OBS_ENCODER_AUDIO;
	packet->timebase_num = 1;
	packet->timebase_den = enc->sample_rate;

	return true;
}