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

/* Variables and functions */
 int /*<<< orphan*/  jim_nvenc_unload () ; 
 int /*<<< orphan*/  obs_ffmpeg_unload_logging () ; 

void obs_module_unload(void)
{
#if ENABLE_FFMPEG_LOGGING
	obs_ffmpeg_unload_logging();
#endif

#ifdef _WIN32
	jim_nvenc_unload();
#endif
}