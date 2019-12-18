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
struct demux_internal {scalar_t__ next_cache_update; int /*<<< orphan*/  lock; int /*<<< orphan*/  eof; scalar_t__ seeking; scalar_t__ back_any_need_recheck; scalar_t__ need_back_seek; scalar_t__ tracks_switched; int /*<<< orphan*/  opts_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_backward_seek (struct demux_internal*) ; 
 int /*<<< orphan*/  execute_seek (struct demux_internal*) ; 
 int /*<<< orphan*/  execute_trackswitch (struct demux_internal*) ; 
 scalar_t__ m_config_cache_update (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  perform_backward_seek (struct demux_internal*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ read_packet (struct demux_internal*) ; 
 int /*<<< orphan*/  update_cache (struct demux_internal*) ; 
 int /*<<< orphan*/  update_opts (struct demux_internal*) ; 

__attribute__((used)) static bool thread_work(struct demux_internal *in)
{
    if (m_config_cache_update(in->opts_cache))
        update_opts(in);
    if (in->tracks_switched) {
        execute_trackswitch(in);
        return true;
    }
    if (in->need_back_seek) {
        perform_backward_seek(in);
        return true;
    }
    if (in->back_any_need_recheck) {
        check_backward_seek(in);
        return true;
    }
    if (in->seeking) {
        execute_seek(in);
        return true;
    }
    if (!in->eof) {
        if (read_packet(in))
            return true; // read_packet unlocked, so recheck conditions
    }
    if (mp_time_us() >= in->next_cache_update) {
        pthread_mutex_unlock(&in->lock);
        update_cache(in);
        pthread_mutex_lock(&in->lock);
        return true;
    }
    return false;
}