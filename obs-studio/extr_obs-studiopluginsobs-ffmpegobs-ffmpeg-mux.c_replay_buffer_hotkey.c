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
struct ffmpeg_muxer {long long save_ts; int /*<<< orphan*/  active; } ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int obs_hotkey_id ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 scalar_t__ os_atomic_load_bool (int /*<<< orphan*/ *) ; 
 long long os_gettime_ns () ; 

__attribute__((used)) static void replay_buffer_hotkey(void *data, obs_hotkey_id id,
		obs_hotkey_t *hotkey, bool pressed)
{
	UNUSED_PARAMETER(id);
	UNUSED_PARAMETER(hotkey);
	UNUSED_PARAMETER(pressed);

	struct ffmpeg_muxer *stream = data;
	if (os_atomic_load_bool(&stream->active))
		stream->save_ts = os_gettime_ns() / 1000LL;
}