#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {unsigned long long tv_sec; } ;
struct _mc_meta_data {unsigned long long slab_config; unsigned long long mmap_base; } ;
struct TYPE_4__ {unsigned long long chunk_size; unsigned long long item_size_max; unsigned long long slab_chunk_size_max; unsigned long long slab_page_size; unsigned long long oldest_live; scalar_t__ oldest_cas; scalar_t__ slab_reassign; scalar_t__ use_cas; scalar_t__ maxbytes; } ;
struct TYPE_3__ {unsigned long long hash_power_level; } ;

/* Variables and functions */
 unsigned long long current_time ; 
 scalar_t__ get_cas_id () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 unsigned long long logger_get_gid () ; 
 scalar_t__ process_started ; 
 int /*<<< orphan*/  restart_set_kv (void*,char*,char*,...) ; 
 TYPE_2__ settings ; 
 TYPE_1__ stats_state ; 

__attribute__((used)) static int _mc_meta_save_cb(const char *tag, void *ctx, void *data) {
    struct _mc_meta_data *meta = (struct _mc_meta_data *)data;

    // Settings to remember.
    // TODO: should get a version of version which is numeric, else
    // comparisons for compat reasons are difficult.
    // it may be possible to punt on this for now; since we can test for the
    // absense of another key... such as the new numeric version.
    //restart_set_kv(ctx, "version", "%s", VERSION);
    // We hold the original factor or subopts _string_
    // it can be directly compared without roundtripping through floats or
    // serializing/deserializing the long options list.
    restart_set_kv(ctx, "slab_config", "%s", meta->slab_config);
    restart_set_kv(ctx, "maxbytes", "%llu", (unsigned long long) settings.maxbytes);
    restart_set_kv(ctx, "chunk_size", "%d", settings.chunk_size);
    restart_set_kv(ctx, "item_size_max", "%d", settings.item_size_max);
    restart_set_kv(ctx, "slab_chunk_size_max", "%d", settings.slab_chunk_size_max);
    restart_set_kv(ctx, "slab_page_size", "%d", settings.slab_page_size);
    restart_set_kv(ctx, "use_cas", "%s", settings.use_cas ? "true" : "false");
    restart_set_kv(ctx, "slab_reassign", "%s", settings.slab_reassign ? "true" : "false");

    // Online state to remember.

    // current time is tough. we need to rely on the clock being correct to
    // pull the delta between stop and start times. we also need to know the
    // delta between start time and now to restore monotonic clocks.
    // for non-monotonic clocks (some OS?), process_started is the only
    // important one.
    restart_set_kv(ctx, "current_time", "%u", current_time);
    // types are great until... this. some systems time_t could be big, but
    // I'm assuming never negative.
    restart_set_kv(ctx, "process_started", "%llu", (unsigned long long) process_started);
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        restart_set_kv(ctx, "stop_time", "%lu", tv.tv_sec);
    }

    // Might as well just fetch the next CAS value to use than tightly
    // coupling the internal variable into the restart system.
    restart_set_kv(ctx, "current_cas", "%llu", (unsigned long long) get_cas_id());
    restart_set_kv(ctx, "oldest_cas", "%llu", (unsigned long long) settings.oldest_cas);
    restart_set_kv(ctx, "logger_gid", "%llu", logger_get_gid());
    restart_set_kv(ctx, "hashpower", "%u", stats_state.hash_power_level);
    // NOTE: oldest_live is a rel_time_t, which aliases for unsigned int.
    // should future proof this with a 64bit upcast, or fetch value from a
    // converter function/macro?
    restart_set_kv(ctx, "oldest_live", "%u", settings.oldest_live);
    // TODO: use uintptr_t etc? is it portable enough?
    restart_set_kv(ctx, "mmap_oldbase", "%p", meta->mmap_base);

    return 0;
}