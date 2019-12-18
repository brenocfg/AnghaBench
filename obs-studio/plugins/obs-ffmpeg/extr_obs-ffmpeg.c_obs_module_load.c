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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  aac_encoder_info ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffmpeg_muxer ; 
 int /*<<< orphan*/  ffmpeg_output ; 
 int /*<<< orphan*/  ffmpeg_source ; 
 int get_win_ver_int () ; 
 int /*<<< orphan*/  jim_nvenc_load () ; 
 int /*<<< orphan*/  nvenc_encoder_info ; 
 scalar_t__ nvenc_supported () ; 
 int /*<<< orphan*/  obs_ffmpeg_load_logging () ; 
 int /*<<< orphan*/  obs_register_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_register_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opus_encoder_info ; 
 int /*<<< orphan*/  replay_buffer ; 
 int /*<<< orphan*/  vaapi_encoder_info ; 
 scalar_t__ vaapi_supported () ; 

bool obs_module_load(void)
{
	obs_register_source(&ffmpeg_source);
	obs_register_output(&ffmpeg_output);
	obs_register_output(&ffmpeg_muxer);
	obs_register_output(&replay_buffer);
	obs_register_encoder(&aac_encoder_info);
	obs_register_encoder(&opus_encoder_info);
#ifndef __APPLE__
	if (nvenc_supported()) {
		blog(LOG_INFO, "NVENC supported");
#ifdef _WIN32
		if (get_win_ver_int() > 0x0601) {
			jim_nvenc_load();
		}
#endif
		obs_register_encoder(&nvenc_encoder_info);
	}
#if !defined(_WIN32) && defined(LIBAVUTIL_VAAPI_AVAILABLE)
	if (vaapi_supported()) {
		blog(LOG_INFO, "FFMPEG VAAPI supported");
		obs_register_encoder(&vaapi_encoder_info);
	}
#endif
#endif

#if ENABLE_FFMPEG_LOGGING
	obs_ffmpeg_load_logging();
#endif
	return true;
}