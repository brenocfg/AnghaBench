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
struct ffmpeg_muxer {scalar_t__ hotkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ffmpeg_mux_destroy (void*) ; 
 int /*<<< orphan*/  obs_hotkey_unregister (scalar_t__) ; 

__attribute__((used)) static void replay_buffer_destroy(void *data)
{
	struct ffmpeg_muxer *stream = data;
	if (stream->hotkey)
		obs_hotkey_unregister(stream->hotkey);
	ffmpeg_mux_destroy(data);
}