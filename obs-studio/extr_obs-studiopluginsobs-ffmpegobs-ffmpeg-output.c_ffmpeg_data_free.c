#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ffmpeg_data {scalar_t__ last_error; TYPE_2__* output; int /*<<< orphan*/ * audio_streams; scalar_t__ video; scalar_t__ initialized; } ;
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* oformat; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  av_write_trailer (TYPE_2__*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 int /*<<< orphan*/  close_audio (struct ffmpeg_data*) ; 
 int /*<<< orphan*/  close_video (struct ffmpeg_data*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ffmpeg_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ffmpeg_data_free(struct ffmpeg_data *data)
{
	if (data->initialized)
		av_write_trailer(data->output);

	if (data->video)
		close_video(data);
	if (data->audio_streams) {
		close_audio(data);
		free(data->audio_streams);
		data->audio_streams = NULL;
	}

	if (data->output) {
		if ((data->output->oformat->flags & AVFMT_NOFILE) == 0)
			avio_close(data->output->pb);

		avformat_free_context(data->output);
	}

	if (data->last_error)
		bfree(data->last_error);

	memset(data, 0, sizeof(struct ffmpeg_data));
}