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
struct ffmpeg_source {int destroy_media; int media_valid; int /*<<< orphan*/  media; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  mp_media_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffmpeg_source_tick(void *data, float seconds)
{
	UNUSED_PARAMETER(seconds);

	struct ffmpeg_source *s = data;
	if (s->destroy_media) {
		if (s->media_valid) {
			mp_media_free(&s->media);
			s->media_valid = false;
		}
		s->destroy_media = false;
	}
}