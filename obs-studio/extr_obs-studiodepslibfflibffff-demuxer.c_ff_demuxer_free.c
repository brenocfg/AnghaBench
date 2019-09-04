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
struct ff_demuxer {int abort; scalar_t__ format_context; int /*<<< orphan*/ * video_decoder; int /*<<< orphan*/ * audio_decoder; struct ff_demuxer* input_format; struct ff_demuxer* input; int /*<<< orphan*/  demuxer_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (struct ff_demuxer*) ; 
 int /*<<< orphan*/  avformat_close_input (scalar_t__*) ; 
 int /*<<< orphan*/  ff_decoder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 

void ff_demuxer_free(struct ff_demuxer *demuxer)
{
	void *demuxer_thread_result;

	demuxer->abort = true;

	pthread_join(demuxer->demuxer_thread, &demuxer_thread_result);

	if (demuxer->input != NULL)
		av_free(demuxer->input);

	if (demuxer->input_format != NULL)
		av_free(demuxer->input_format);

	if (demuxer->audio_decoder != NULL)
		ff_decoder_free(demuxer->audio_decoder);

	if (demuxer->video_decoder != NULL)
		ff_decoder_free(demuxer->video_decoder);

	if (demuxer->format_context)
		avformat_close_input(&demuxer->format_context);

	av_free(demuxer);
}