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
struct playlist_entry {int dummy; } ;
struct MPContext {scalar_t__ stop_play; int /*<<< orphan*/ * encode_lavc_ctx; TYPE_1__* opts; TYPE_2__* playlist; } ;
struct TYPE_4__ {int current_was_replaced; struct playlist_entry* current; } ;
struct TYPE_3__ {int player_idle_mode; } ;

/* Variables and functions */
 scalar_t__ AT_END_OF_FILE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*) ; 
 scalar_t__ PT_ERROR ; 
 scalar_t__ PT_NEXT_ENTRY ; 
 scalar_t__ PT_QUIT ; 
 scalar_t__ PT_STOP ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  cancel_open (struct MPContext*) ; 
 int /*<<< orphan*/  encode_lavc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_loop (struct MPContext*) ; 
 int /*<<< orphan*/  mp_clients_all_initialized (struct MPContext*) ; 
 int /*<<< orphan*/  mp_idle (struct MPContext*) ; 
 struct playlist_entry* mp_next_file (struct MPContext*,int,int,int) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  play_current_file (struct MPContext*) ; 
 int /*<<< orphan*/  prepare_playlist (struct MPContext*,TYPE_2__*) ; 
 int /*<<< orphan*/  uninit_audio_out (struct MPContext*) ; 
 int /*<<< orphan*/  uninit_video_out (struct MPContext*) ; 

void mp_play_files(struct MPContext *mpctx)
{
    // Wait for all scripts to load before possibly starting playback.
    if (!mp_clients_all_initialized(mpctx)) {
        MP_VERBOSE(mpctx, "Waiting for scripts...\n");
        while (!mp_clients_all_initialized(mpctx))
            mp_idle(mpctx);
        mp_wakeup_core(mpctx); // avoid lost wakeups during waiting
        MP_VERBOSE(mpctx, "Done loading scripts.\n");
    }

    prepare_playlist(mpctx, mpctx->playlist);

    for (;;) {
        assert(mpctx->stop_play);
        idle_loop(mpctx);
        if (mpctx->stop_play == PT_QUIT)
            break;

        play_current_file(mpctx);
        if (mpctx->stop_play == PT_QUIT)
            break;

        struct playlist_entry *new_entry = mpctx->playlist->current;
        if (mpctx->stop_play == PT_NEXT_ENTRY || mpctx->stop_play == PT_ERROR ||
            mpctx->stop_play == AT_END_OF_FILE || mpctx->stop_play == PT_STOP)
        {
            new_entry = mp_next_file(mpctx, +1, false, true);
        }

        mpctx->playlist->current = new_entry;
        mpctx->playlist->current_was_replaced = false;
        mpctx->stop_play = PT_STOP;

        if (!mpctx->playlist->current && mpctx->opts->player_idle_mode < 2)
            break;
    }

    cancel_open(mpctx);

    if (mpctx->encode_lavc_ctx) {
        // Make sure all streams get finished.
        uninit_audio_out(mpctx);
        uninit_video_out(mpctx);

        if (!encode_lavc_free(mpctx->encode_lavc_ctx))
            mpctx->stop_play = PT_ERROR;

        mpctx->encode_lavc_ctx = NULL;
    }
}