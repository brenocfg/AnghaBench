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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_audio_info ) (int /*<<< orphan*/ ,struct audio_convert_info*) ;} ;
struct obs_encoder {TYPE_2__ context; TYPE_1__ info; int /*<<< orphan*/  media; } ;
struct audio_output_info {int /*<<< orphan*/  speakers; int /*<<< orphan*/  samples_per_sec; int /*<<< orphan*/  format; } ;
struct audio_convert_info {int /*<<< orphan*/  speakers; int /*<<< orphan*/  samples_per_sec; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  SPEAKERS_UNKNOWN ; 
 struct audio_output_info* audio_output_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct audio_convert_info*) ; 

__attribute__((used)) static inline void get_audio_info(const struct obs_encoder *encoder,
				  struct audio_convert_info *info)
{
	const struct audio_output_info *aoi;
	aoi = audio_output_get_info(encoder->media);

	if (info->format == AUDIO_FORMAT_UNKNOWN)
		info->format = aoi->format;
	if (!info->samples_per_sec)
		info->samples_per_sec = aoi->samples_per_sec;
	if (info->speakers == SPEAKERS_UNKNOWN)
		info->speakers = aoi->speakers;

	if (encoder->info.get_audio_info)
		encoder->info.get_audio_info(encoder->context.data, info);
}