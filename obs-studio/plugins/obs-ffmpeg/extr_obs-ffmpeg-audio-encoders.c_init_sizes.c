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
struct enc_encoder {int /*<<< orphan*/  audio_size; int /*<<< orphan*/  audio_planes; TYPE_1__* context; } ;
struct audio_output_info {int /*<<< orphan*/  speakers; } ;
typedef  enum audio_format { ____Placeholder_audio_format } audio_format ;
typedef  int /*<<< orphan*/  audio_t ;
struct TYPE_2__ {int /*<<< orphan*/  sample_fmt; } ;

/* Variables and functions */
 struct audio_output_info* audio_output_get_info (int /*<<< orphan*/ *) ; 
 int convert_ffmpeg_sample_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_audio_planes (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_audio_size (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_sizes(struct enc_encoder *enc, audio_t *audio)
{
	const struct audio_output_info *aoi;
	enum audio_format format;

	aoi = audio_output_get_info(audio);
	format = convert_ffmpeg_sample_format(enc->context->sample_fmt);

	enc->audio_planes = get_audio_planes(format, aoi->speakers);
	enc->audio_size = get_audio_size(format, aoi->speakers, 1);
}