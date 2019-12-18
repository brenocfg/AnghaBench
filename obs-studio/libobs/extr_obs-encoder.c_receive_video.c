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
struct video_data {scalar_t__ timestamp; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct obs_encoder {scalar_t__ first_raw_ts; scalar_t__ start_ts; scalar_t__ timebase_num; int /*<<< orphan*/  cur_pts; int /*<<< orphan*/  pause; int /*<<< orphan*/  first_received; struct obs_encoder* paired_encoder; } ;
struct encoder_frame {int frames; int /*<<< orphan*/  pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t MAX_AV_PLANES ; 
 scalar_t__ do_encode (struct obs_encoder*,struct encoder_frame*) ; 
 int /*<<< orphan*/  memset (struct encoder_frame*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receive_video_name ; 
 scalar_t__ video_pause_check (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void receive_video(void *param, struct video_data *frame)
{
	profile_start(receive_video_name);

	struct obs_encoder *encoder = param;
	struct obs_encoder *pair = encoder->paired_encoder;
	struct encoder_frame enc_frame;

	if (!encoder->first_received && pair) {
		if (!pair->first_received ||
		    pair->first_raw_ts > frame->timestamp) {
			goto wait_for_audio;
		}
	}

	if (video_pause_check(&encoder->pause, frame->timestamp))
		goto wait_for_audio;

	memset(&enc_frame, 0, sizeof(struct encoder_frame));

	for (size_t i = 0; i < MAX_AV_PLANES; i++) {
		enc_frame.data[i] = frame->data[i];
		enc_frame.linesize[i] = frame->linesize[i];
	}

	if (!encoder->start_ts)
		encoder->start_ts = frame->timestamp;

	enc_frame.frames = 1;
	enc_frame.pts = encoder->cur_pts;

	if (do_encode(encoder, &enc_frame))
		encoder->cur_pts += encoder->timebase_num;

wait_for_audio:
	profile_end(receive_video_name);
}