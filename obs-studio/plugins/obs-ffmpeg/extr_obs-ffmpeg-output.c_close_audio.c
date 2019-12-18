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
struct ffmpeg_data {int num_audio_streams; scalar_t__* aframe; TYPE_1__** audio_streams; scalar_t__** samples; int /*<<< orphan*/ ** excess_frames; } ;
struct TYPE_2__ {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 size_t MAX_AV_PLANES ; 
 int /*<<< orphan*/  av_frame_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int /*<<< orphan*/  avcodec_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_audio(struct ffmpeg_data *data)
{
	for (int idx = 0; idx < data->num_audio_streams; idx++) {
		for (size_t i = 0; i < MAX_AV_PLANES; i++)
			circlebuf_free(&data->excess_frames[idx][i]);

		if (data->samples[idx][0])
			av_freep(&data->samples[idx][0]);
		if (data->audio_streams[idx])
			avcodec_close(data->audio_streams[idx]->codec);
		if (data->aframe[idx])
			av_frame_free(&data->aframe[idx]);
	}
}