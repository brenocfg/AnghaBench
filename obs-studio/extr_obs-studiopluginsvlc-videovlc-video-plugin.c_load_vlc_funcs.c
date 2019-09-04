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
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char*) ; 
 void* libvlc_audio_set_callbacks_ ; 
 void* libvlc_audio_set_format_callbacks_ ; 
 void* libvlc_clock_ ; 
 void* libvlc_event_attach_ ; 
 void* libvlc_media_add_option_ ; 
 void* libvlc_media_list_add_media_ ; 
 void* libvlc_media_list_event_manager_ ; 
 void* libvlc_media_list_lock_ ; 
 void* libvlc_media_list_new_ ; 
 void* libvlc_media_list_player_event_manager_ ; 
 void* libvlc_media_list_player_new_ ; 
 void* libvlc_media_list_player_next_ ; 
 void* libvlc_media_list_player_pause_ ; 
 void* libvlc_media_list_player_play_ ; 
 void* libvlc_media_list_player_previous_ ; 
 void* libvlc_media_list_player_release_ ; 
 void* libvlc_media_list_player_set_media_list_ ; 
 void* libvlc_media_list_player_set_media_player_ ; 
 void* libvlc_media_list_player_set_playback_mode_ ; 
 void* libvlc_media_list_player_stop_ ; 
 void* libvlc_media_list_release_ ; 
 void* libvlc_media_list_unlock_ ; 
 void* libvlc_media_new_location_ ; 
 void* libvlc_media_new_path_ ; 
 void* libvlc_media_player_event_manager_ ; 
 void* libvlc_media_player_get_time_ ; 
 void* libvlc_media_player_new_ ; 
 void* libvlc_media_player_new_from_media_ ; 
 void* libvlc_media_player_play_ ; 
 void* libvlc_media_player_release_ ; 
 void* libvlc_media_player_stop_ ; 
 void* libvlc_media_release_ ; 
 void* libvlc_media_retain_ ; 
 int /*<<< orphan*/  libvlc_module ; 
 void* libvlc_new_ ; 
 void* libvlc_release_ ; 
 void* libvlc_video_get_size_ ; 
 void* libvlc_video_set_callbacks_ ; 
 void* libvlc_video_set_format_callbacks_ ; 
 void* os_dlsym (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool load_vlc_funcs(void)
{
#define LOAD_VLC_FUNC(func) \
	do { \
		func ## _ = os_dlsym(libvlc_module, #func); \
		if (!func ## _) { \
			blog(LOG_WARNING, "Could not func VLC function %s, " \
					"VLC loading failed", #func); \
			return false; \
		} \
	} while (false)

	/* libvlc core */
	LOAD_VLC_FUNC(libvlc_new);
	LOAD_VLC_FUNC(libvlc_release);
	LOAD_VLC_FUNC(libvlc_clock);
	LOAD_VLC_FUNC(libvlc_event_attach);

	/* libvlc media */
	LOAD_VLC_FUNC(libvlc_media_new_path);
	LOAD_VLC_FUNC(libvlc_media_new_location);
	LOAD_VLC_FUNC(libvlc_media_add_option);
	LOAD_VLC_FUNC(libvlc_media_release);
	LOAD_VLC_FUNC(libvlc_media_retain);

	/* libvlc media player */
	LOAD_VLC_FUNC(libvlc_media_player_new);
	LOAD_VLC_FUNC(libvlc_media_player_new_from_media);
	LOAD_VLC_FUNC(libvlc_media_player_release);
	LOAD_VLC_FUNC(libvlc_video_set_callbacks);
	LOAD_VLC_FUNC(libvlc_video_set_format_callbacks);
	LOAD_VLC_FUNC(libvlc_audio_set_callbacks);
	LOAD_VLC_FUNC(libvlc_audio_set_format_callbacks);
	LOAD_VLC_FUNC(libvlc_media_player_play);
	LOAD_VLC_FUNC(libvlc_media_player_stop);
	LOAD_VLC_FUNC(libvlc_media_player_get_time);
	LOAD_VLC_FUNC(libvlc_video_get_size);
	LOAD_VLC_FUNC(libvlc_media_player_event_manager);

	/* libvlc media list */
	LOAD_VLC_FUNC(libvlc_media_list_new);
	LOAD_VLC_FUNC(libvlc_media_list_release);
	LOAD_VLC_FUNC(libvlc_media_list_add_media);
	LOAD_VLC_FUNC(libvlc_media_list_lock);
	LOAD_VLC_FUNC(libvlc_media_list_unlock);
	LOAD_VLC_FUNC(libvlc_media_list_event_manager);

	/* libvlc media list player */
	LOAD_VLC_FUNC(libvlc_media_list_player_new);
	LOAD_VLC_FUNC(libvlc_media_list_player_release);
	LOAD_VLC_FUNC(libvlc_media_list_player_play);
	LOAD_VLC_FUNC(libvlc_media_list_player_pause);
	LOAD_VLC_FUNC(libvlc_media_list_player_stop);
	LOAD_VLC_FUNC(libvlc_media_list_player_set_media_player);
	LOAD_VLC_FUNC(libvlc_media_list_player_set_media_list);
	LOAD_VLC_FUNC(libvlc_media_list_player_event_manager);
	LOAD_VLC_FUNC(libvlc_media_list_player_set_playback_mode);
	LOAD_VLC_FUNC(libvlc_media_list_player_next);
	LOAD_VLC_FUNC(libvlc_media_list_player_previous);
	return true;
}