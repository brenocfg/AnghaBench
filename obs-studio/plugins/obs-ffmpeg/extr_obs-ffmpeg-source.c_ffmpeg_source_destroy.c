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
struct ffmpeg_source {struct ffmpeg_source* input_format; struct ffmpeg_source* input; struct ffmpeg_source* sws_data; int /*<<< orphan*/ * sws_ctx; int /*<<< orphan*/  media; scalar_t__ media_valid; scalar_t__ hotkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct ffmpeg_source*) ; 
 int /*<<< orphan*/  mp_media_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_hotkey_unregister (scalar_t__) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffmpeg_source_destroy(void *data)
{
	struct ffmpeg_source *s = data;

	if (s->hotkey)
		obs_hotkey_unregister(s->hotkey);
	if (s->media_valid)
		mp_media_free(&s->media);

	if (s->sws_ctx != NULL)
		sws_freeContext(s->sws_ctx);
	bfree(s->sws_data);
	bfree(s->input);
	bfree(s->input_format);
	bfree(s);
}