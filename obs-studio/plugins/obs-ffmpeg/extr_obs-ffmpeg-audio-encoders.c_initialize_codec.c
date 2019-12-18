#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct enc_encoder {int frame_size; int frame_size_bytes; TYPE_1__* context; int /*<<< orphan*/  samples; scalar_t__ audio_size; TYPE_2__* aframe; int /*<<< orphan*/  codec; } ;
struct TYPE_4__ {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int frame_size; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_err2str (int) ; 
 TYPE_2__* av_frame_alloc () ; 
 int av_samples_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avcodec_open2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static bool initialize_codec(struct enc_encoder *enc)
{
	int ret;

	enc->aframe = av_frame_alloc();
	if (!enc->aframe) {
		warn("Failed to allocate audio frame");
		return false;
	}

	ret = avcodec_open2(enc->context, enc->codec, NULL);
	if (ret < 0) {
		warn("Failed to open AAC codec: %s", av_err2str(ret));
		return false;
	}
	enc->aframe->format = enc->context->sample_fmt;
	enc->aframe->channels = enc->context->channels;
	enc->aframe->channel_layout = enc->context->channel_layout;
	enc->aframe->sample_rate = enc->context->sample_rate;

	enc->frame_size = enc->context->frame_size;
	if (!enc->frame_size)
		enc->frame_size = 1024;

	enc->frame_size_bytes = enc->frame_size * (int)enc->audio_size;

	ret = av_samples_alloc(enc->samples, NULL, enc->context->channels,
			       enc->frame_size, enc->context->sample_fmt, 0);
	if (ret < 0) {
		warn("Failed to create audio buffer: %s", av_err2str(ret));
		return false;
	}

	return true;
}