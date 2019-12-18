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
struct ffmpeg_source {int /*<<< orphan*/  source; scalar_t__ is_local_file; int /*<<< orphan*/  is_looping; int /*<<< orphan*/  media; scalar_t__ media_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ffmpeg_source_open (struct ffmpeg_source*) ; 
 int /*<<< orphan*/  mp_media_play (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_show_preloaded_video (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmpeg_source_start(struct ffmpeg_source *s)
{
	if (!s->media_valid)
		ffmpeg_source_open(s);

	if (s->media_valid) {
		mp_media_play(&s->media, s->is_looping);
		if (s->is_local_file)
			obs_source_show_preloaded_video(s->source);
	}
}