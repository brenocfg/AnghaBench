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
struct mp_decode {int /*<<< orphan*/  pkt; int /*<<< orphan*/  frame; int /*<<< orphan*/  decoder; scalar_t__ audio; } ;

/* Variables and functions */
 int avcodec_decode_audio4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int avcodec_decode_video2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_packet(struct mp_decode *d, int *got_frame)
{
	int ret;
	*got_frame = 0;

#ifdef USE_NEW_FFMPEG_DECODE_API
	ret = avcodec_receive_frame(d->decoder, d->frame);
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

		ret = avcodec_receive_frame(d->decoder, d->frame);
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
		ret = avcodec_decode_audio4(d->decoder,
				d->frame, got_frame, &d->pkt);
	} else {
		ret = avcodec_decode_video2(d->decoder,
				d->frame, got_frame, &d->pkt);
	}
#endif
	return ret;
}