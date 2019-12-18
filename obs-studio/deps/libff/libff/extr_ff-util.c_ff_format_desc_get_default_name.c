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
struct ff_format_desc {int /*<<< orphan*/  video_codec; int /*<<< orphan*/  audio_codec; } ;
typedef  enum ff_codec_type { ____Placeholder_ff_codec_type } ff_codec_type ;

/* Variables and functions */
#define  FF_CODEC_AUDIO 129 
#define  FF_CODEC_VIDEO 128 
 char const* get_encoder_name (struct ff_format_desc const*,int /*<<< orphan*/ ) ; 

const char *
ff_format_desc_get_default_name(const struct ff_format_desc *format_desc,
                                enum ff_codec_type codec_type)
{
	switch (codec_type) {
	case FF_CODEC_AUDIO:
		return get_encoder_name(format_desc, format_desc->audio_codec);
	case FF_CODEC_VIDEO:
		return get_encoder_name(format_desc, format_desc->video_codec);
	default:
		return NULL;
	}
}