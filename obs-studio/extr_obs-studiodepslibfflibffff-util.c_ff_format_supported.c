#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  struct ff_format_desc {struct ff_format_desc const* next; int /*<<< orphan*/  codec_tags; int /*<<< orphan*/  extensions; int /*<<< orphan*/  mime_type; int /*<<< orphan*/  long_name; int /*<<< orphan*/  name; int /*<<< orphan*/  video_codec; int /*<<< orphan*/  audio_codec; } const ff_format_desc ;
struct TYPE_4__ {int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  extensions; int /*<<< orphan*/  mime_type; int /*<<< orphan*/  long_name; int /*<<< orphan*/  name; int /*<<< orphan*/  video_codec; int /*<<< orphan*/  audio_codec; int /*<<< orphan*/  priv_class; } ;
typedef  TYPE_1__ AVOutputFormat ;

/* Variables and functions */
 struct ff_format_desc const* av_mallocz (int) ; 
 TYPE_1__* av_oformat_next (TYPE_1__*) ; 
 scalar_t__ is_output_device (int /*<<< orphan*/ ) ; 

const struct ff_format_desc *ff_format_supported()
{
	AVOutputFormat *output_format = NULL;
	struct ff_format_desc *desc = NULL;
	struct ff_format_desc *current = NULL;

	while ((output_format = av_oformat_next(output_format)) != NULL) {
		struct ff_format_desc *d;
		if (is_output_device(output_format->priv_class))
			continue;

		d = av_mallocz(sizeof(struct ff_format_desc));

		d->audio_codec = output_format->audio_codec;
		d->video_codec = output_format->video_codec;
		d->name = output_format->name;
		d->long_name = output_format->long_name;
		d->mime_type = output_format->mime_type;
		d->extensions = output_format->extensions;
		d->codec_tags = output_format->codec_tag;

		if (current != NULL) {
			current->next = d;
			current = d;
		} else {
			desc = current = d;
		}
	}

	return desc;
}