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
struct TYPE_2__ {int tracks; } ;
struct ffmpeg_mux {int /*<<< orphan*/ * audio; int /*<<< orphan*/ * audio_header; TYPE_1__ params; int /*<<< orphan*/  video_header; int /*<<< orphan*/  output; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_write_trailer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_avformat (struct ffmpeg_mux*) ; 
 int /*<<< orphan*/  header_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ffmpeg_mux*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ffmpeg_mux_free(struct ffmpeg_mux *ffm)
{
	if (ffm->initialized) {
		av_write_trailer(ffm->output);
	}

	free_avformat(ffm);

	header_free(&ffm->video_header);

	if (ffm->audio_header) {
		for (int i = 0; i < ffm->params.tracks; i++) {
			header_free(&ffm->audio_header[i]);
		}

		free(ffm->audio_header);
	}

	if (ffm->audio) {
		free(ffm->audio);
	}

	memset(ffm, 0, sizeof(*ffm));
}