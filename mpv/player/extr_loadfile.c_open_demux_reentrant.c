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
struct MPContext {char* stream_open_filename; int /*<<< orphan*/  open_res_error; int /*<<< orphan*/  error_playing; int /*<<< orphan*/  playback_abort; TYPE_2__* demuxer; TYPE_2__* open_res_demuxer; scalar_t__ stop_play; int /*<<< orphan*/  open_done; int /*<<< orphan*/  open_cancel; TYPE_1__* playing; scalar_t__ open_active; int /*<<< orphan*/  open_url; } ;
struct TYPE_4__ {int /*<<< orphan*/  cancel; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_open (struct MPContext*) ; 
 int /*<<< orphan*/  mp_abort_playback_async (struct MPContext*) ; 
 int /*<<< orphan*/  mp_cancel_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_idle (struct MPContext*) ; 
 int /*<<< orphan*/  start_open (struct MPContext*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void open_demux_reentrant(struct MPContext *mpctx)
{
    char *url = mpctx->stream_open_filename;

    if (mpctx->open_active) {
        bool done = atomic_load(&mpctx->open_done);
        bool failed = done && !mpctx->open_res_demuxer;
        bool correct_url = strcmp(mpctx->open_url, url) == 0;

        if (correct_url && !failed) {
            MP_VERBOSE(mpctx, "Using prefetched/prefetching URL.\n");
        } else if (correct_url && failed) {
            MP_VERBOSE(mpctx, "Prefetched URL failed, retrying.\n");
            cancel_open(mpctx);
        } else {
            if (done) {
                MP_VERBOSE(mpctx, "Dropping finished prefetch of wrong URL.\n");
            } else {
                MP_VERBOSE(mpctx, "Aborting ongoing prefetch of wrong URL.\n");
            }
            cancel_open(mpctx);
        }
    }

    if (!mpctx->open_active)
        start_open(mpctx, url, mpctx->playing->stream_flags, false);

    // User abort should cancel the opener now.
    mp_cancel_set_parent(mpctx->open_cancel, mpctx->playback_abort);

    while (!atomic_load(&mpctx->open_done)) {
        mp_idle(mpctx);

        if (mpctx->stop_play)
            mp_abort_playback_async(mpctx);
    }

    if (mpctx->open_res_demuxer) {
        mpctx->demuxer = mpctx->open_res_demuxer;
        mpctx->open_res_demuxer = NULL;
        mp_cancel_set_parent(mpctx->demuxer->cancel, mpctx->playback_abort);
    } else {
        mpctx->error_playing = mpctx->open_res_error;
    }

    cancel_open(mpctx); // cleanup
}