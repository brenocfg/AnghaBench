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
struct mpv_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_log_default_callback ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_lock ; 
 struct mpv_global* log_mpv_instance ; 
 int /*<<< orphan*/  log_root ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

void uninit_libav(struct mpv_global *global)
{
    pthread_mutex_lock(&log_lock);
    if (log_mpv_instance == global) {
        av_log_set_callback(av_log_default_callback);
        log_mpv_instance = NULL;
        talloc_free(log_root);
    }
    pthread_mutex_unlock(&log_lock);
}