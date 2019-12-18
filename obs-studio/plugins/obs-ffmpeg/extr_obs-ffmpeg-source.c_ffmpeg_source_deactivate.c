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
struct ffmpeg_source {int /*<<< orphan*/  source; scalar_t__ is_clear_on_media_end; int /*<<< orphan*/  media; scalar_t__ media_valid; scalar_t__ restart_on_activate; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_media_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_output_video (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffmpeg_source_deactivate(void *data)
{
	struct ffmpeg_source *s = data;

	if (s->restart_on_activate) {
		if (s->media_valid) {
			mp_media_stop(&s->media);

			if (s->is_clear_on_media_end)
				obs_source_output_video(s->source, NULL);
		}
	}
}