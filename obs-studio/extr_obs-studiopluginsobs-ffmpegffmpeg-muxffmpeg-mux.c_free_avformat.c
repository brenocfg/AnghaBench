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
struct ffmpeg_mux {scalar_t__ num_audio_streams; int /*<<< orphan*/ * audio_streams; int /*<<< orphan*/ * video_stream; TYPE_2__* output; } ;
struct TYPE_4__ {int /*<<< orphan*/  pb; TYPE_1__* oformat; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_avformat(struct ffmpeg_mux *ffm)
{
	if (ffm->output) {
		if ((ffm->output->oformat->flags & AVFMT_NOFILE) == 0)
			avio_close(ffm->output->pb);

		avformat_free_context(ffm->output);
		ffm->output = NULL;
	}

	if (ffm->audio_streams) {
		free(ffm->audio_streams);
	}

	ffm->video_stream = NULL;
	ffm->audio_streams = NULL;
	ffm->num_audio_streams = 0;
}