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
struct mpv_global {int /*<<< orphan*/ * log; } ;

/* Variables and functions */
 char* LIB_PREFIX ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avdevice_register_all () ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 void* log_decaudio ; 
 void* log_decvideo ; 
 void* log_demuxer ; 
 int /*<<< orphan*/  log_lock ; 
 struct mpv_global* log_mpv_instance ; 
 int /*<<< orphan*/ * log_root ; 
 void* mp_log_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_msg_av_log_callback ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void init_libav(struct mpv_global *global)
{
    pthread_mutex_lock(&log_lock);
    if (!log_mpv_instance) {
        log_mpv_instance = global;
        log_root = mp_log_new(NULL, global->log, LIB_PREFIX);
        log_decaudio = mp_log_new(log_root, log_root, "audio");
        log_decvideo = mp_log_new(log_root, log_root, "video");
        log_demuxer = mp_log_new(log_root, log_root, "demuxer");
        av_log_set_callback(mp_msg_av_log_callback);
    }
    pthread_mutex_unlock(&log_lock);

    avformat_network_init();

#if HAVE_LIBAVDEVICE
    avdevice_register_all();
#endif
}