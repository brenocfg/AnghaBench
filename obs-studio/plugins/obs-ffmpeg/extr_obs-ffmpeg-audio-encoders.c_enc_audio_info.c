#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct enc_encoder {TYPE_1__* context; } ;
struct audio_convert_info {int /*<<< orphan*/  speakers; scalar_t__ samples_per_sec; int /*<<< orphan*/  format; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel_layout; scalar_t__ sample_rate; int /*<<< orphan*/  sample_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  convert_ff_channel_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_ffmpeg_sample_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enc_audio_info(void *data, struct audio_convert_info *info)
{
	struct enc_encoder *enc = data;
	info->format = convert_ffmpeg_sample_format(enc->context->sample_fmt);
	info->samples_per_sec = (uint32_t)enc->context->sample_rate;
	info->speakers =
		convert_ff_channel_layout(enc->context->channel_layout);
}