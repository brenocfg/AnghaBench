#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; } ;
struct mp_decode {scalar_t__ hw_format; TYPE_4__* sw_frame; TYPE_4__* frame; TYPE_4__* hw_frame; scalar_t__ hw; TYPE_1__ pkt; int /*<<< orphan*/  in_frame; int /*<<< orphan*/  decoder; scalar_t__ audio; } ;
struct TYPE_7__ {scalar_t__ format; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int av_hwframe_transfer_data (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int avcodec_decode_audio4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int avcodec_decode_video2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int avcodec_receive_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avcodec_send_packet (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int decode_packet(struct mp_decode *d, int *got_frame)
{
	int ret;
	*got_frame = 0;

#ifdef USE_NEW_FFMPEG_DECODE_API
	ret = avcodec_receive_frame(d->decoder, d->in_frame);
	if (ret != 0 && ret != AVERROR(EAGAIN)) {
		if (ret == AVERROR_EOF)
			ret = 0;
		return ret;
	}

	if (ret != 0) {
		ret = avcodec_send_packet(d->decoder, &d->pkt);
		if (ret != 0 && ret != AVERROR(EAGAIN)) {
			if (ret == AVERROR_EOF)
				ret = 0;
			return ret;
		}

		ret = avcodec_receive_frame(d->decoder, d->in_frame);
		if (ret != 0 && ret != AVERROR(EAGAIN)) {
			if (ret == AVERROR_EOF)
				ret = 0;
			return ret;
		}

		*got_frame = (ret == 0);
		ret = d->pkt.size;
	} else {
		ret = 0;
		*got_frame = 1;
	}

#else
	if (d->audio) {
		ret = avcodec_decode_audio4(d->decoder, d->in_frame, got_frame,
					    &d->pkt);
	} else {
		ret = avcodec_decode_video2(d->decoder, d->in_frame, got_frame,
					    &d->pkt);
	}
#endif

#ifdef USE_NEW_HARDWARE_CODEC_METHOD
	if (*got_frame && d->hw) {
		if (d->hw_frame->format != d->hw_format) {
			d->frame = d->hw_frame;
			return ret;
		}

		int err = av_hwframe_transfer_data(d->sw_frame, d->hw_frame, 0);
		if (err != 0) {
			ret = 0;
			*got_frame = false;
		}
	}
#endif

	d->frame = d->sw_frame;
	return ret;
}