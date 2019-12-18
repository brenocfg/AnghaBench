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
typedef  void* uint32_t ;
struct obs_encoder {size_t planes; scalar_t__ framesize; int /*<<< orphan*/  cur_pts; scalar_t__ framesize_bytes; int /*<<< orphan*/ * audio_output_buffer; int /*<<< orphan*/ * audio_input_buffer; } ;
struct encoder_frame {int /*<<< orphan*/  pts; void* frames; void** linesize; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_pop_front (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  do_encode (struct obs_encoder*,struct encoder_frame*) ; 
 int /*<<< orphan*/  memset (struct encoder_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool send_audio_data(struct obs_encoder *encoder)
{
	struct encoder_frame enc_frame;

	memset(&enc_frame, 0, sizeof(struct encoder_frame));

	for (size_t i = 0; i < encoder->planes; i++) {
		circlebuf_pop_front(&encoder->audio_input_buffer[i],
				    encoder->audio_output_buffer[i],
				    encoder->framesize_bytes);

		enc_frame.data[i] = encoder->audio_output_buffer[i];
		enc_frame.linesize[i] = (uint32_t)encoder->framesize_bytes;
	}

	enc_frame.frames = (uint32_t)encoder->framesize;
	enc_frame.pts = encoder->cur_pts;

	if (!do_encode(encoder, &enc_frame))
		return false;

	encoder->cur_pts += encoder->framesize;
	return true;
}