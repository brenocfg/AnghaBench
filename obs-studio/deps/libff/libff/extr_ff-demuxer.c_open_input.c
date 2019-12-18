#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  custom_options; } ;
struct ff_demuxer {TYPE_1__ options; int /*<<< orphan*/  input; int /*<<< orphan*/ * input_format; } ;
struct TYPE_9__ {struct ff_demuxer* opaque; int /*<<< orphan*/  callback; } ;
struct TYPE_10__ {TYPE_2__ interrupt_callback; } ;
typedef  int /*<<< orphan*/  AVInputFormat ;
typedef  TYPE_2__ AVIOInterruptCB ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/ * av_find_input_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__* avformat_alloc_context () ; 
 scalar_t__ avformat_find_stream_info (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avformat_open_input (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  demuxer_interrupted_callback ; 

__attribute__((used)) static bool open_input(struct ff_demuxer *demuxer,
                       AVFormatContext **format_context)
{
	AVInputFormat *input_format = NULL;

	AVIOInterruptCB interrupted_callback;
	interrupted_callback.callback = demuxer_interrupted_callback;
	interrupted_callback.opaque = demuxer;

	*format_context = avformat_alloc_context();
	(*format_context)->interrupt_callback = interrupted_callback;

	if (demuxer->input_format != NULL) {
		input_format = av_find_input_format(demuxer->input_format);
		if (input_format == NULL)
			av_log(NULL, AV_LOG_WARNING,
			       "unable to find input "
			       "format %s",
			       demuxer->input_format);
	}

	if (avformat_open_input(format_context, demuxer->input, input_format,
	                        &demuxer->options.custom_options) != 0)
		return false;

	return avformat_find_stream_info(*format_context, NULL) >= 0;
}