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
struct ffmpeg_data {int /*<<< orphan*/  vframe; TYPE_2__* vcodec; TYPE_1__* video; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_3__ {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_A64_MULTI ; 
 scalar_t__ AV_CODEC_ID_A64_MULTI5 ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_video(struct ffmpeg_data *data)
{
	avcodec_close(data->video->codec);
	av_frame_unref(data->vframe);

	// This format for some reason derefs video frame
	// too many times
	if (data->vcodec->id == AV_CODEC_ID_A64_MULTI ||
	    data->vcodec->id == AV_CODEC_ID_A64_MULTI5)
		return;

	av_frame_free(&data->vframe);
}