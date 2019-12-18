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
struct ffmpeg_source {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int obs_hotkey_id ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  ffmpeg_source_start (struct ffmpeg_source*) ; 
 scalar_t__ obs_source_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void restart_hotkey(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey,
			   bool pressed)
{
	UNUSED_PARAMETER(id);
	UNUSED_PARAMETER(hotkey);
	UNUSED_PARAMETER(pressed);

	struct ffmpeg_source *s = data;
	if (obs_source_active(s->source))
		ffmpeg_source_start(s);
}