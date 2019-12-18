#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ff_format_desc {int dummy; } ;
typedef  struct ff_codec_desc const ff_codec_desc ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ AVCodecDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (void*) ; 
 int /*<<< orphan*/  get_codecs (TYPE_1__ const***,unsigned int*) ; 
 int /*<<< orphan*/  get_codecs_for_id (struct ff_format_desc const*,struct ff_codec_desc const**,struct ff_codec_desc const**,int /*<<< orphan*/ ,int) ; 

const struct ff_codec_desc *
ff_codec_supported(const struct ff_format_desc *format_desc,
                   bool ignore_compatability)
{
	const AVCodecDescriptor **codecs;
	unsigned int size;
	unsigned int i;
	struct ff_codec_desc *current = NULL;
	struct ff_codec_desc *first = NULL;

	if (!get_codecs(&codecs, &size))
		return NULL;

	for (i = 0; i < size; i++) {
		const AVCodecDescriptor *codec = codecs[i];
		get_codecs_for_id(format_desc, &first, &current, codec->id,
		                  ignore_compatability);
	}

	av_free((void *)codecs);

	return first;
}