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
struct MPContext {scalar_t__ video_status; int /*<<< orphan*/  filter_root; scalar_t__ stop_play; int /*<<< orphan*/  playback_pts; scalar_t__ lavfi; int /*<<< orphan*/  encode_lavc_ctx; } ;

/* Variables and functions */
 scalar_t__ AT_END_OF_FILE ; 
 scalar_t__ PT_QUIT ; 
 scalar_t__ STATUS_EOF ; 
 scalar_t__ encode_lavc_didfail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_queued_seek (struct MPContext*) ; 
 int /*<<< orphan*/  fill_audio_out_buffers (struct MPContext*) ; 
 int /*<<< orphan*/  handle_chapter_change (struct MPContext*) ; 
 int /*<<< orphan*/  handle_command_updates (struct MPContext*) ; 
 int /*<<< orphan*/  handle_cursor_autohide (struct MPContext*) ; 
 int /*<<< orphan*/  handle_delayed_audio_seek (struct MPContext*) ; 
 int /*<<< orphan*/  handle_dummy_ticks (struct MPContext*) ; 
 int /*<<< orphan*/  handle_eof (struct MPContext*) ; 
 int /*<<< orphan*/  handle_force_window (struct MPContext*,int) ; 
 int /*<<< orphan*/  handle_keep_open (struct MPContext*) ; 
 int /*<<< orphan*/  handle_loop_file (struct MPContext*) ; 
 int /*<<< orphan*/  handle_osd_redraw (struct MPContext*) ; 
 int /*<<< orphan*/  handle_playback_restart (struct MPContext*) ; 
 int /*<<< orphan*/  handle_playback_time (struct MPContext*) ; 
 int /*<<< orphan*/  handle_sstep (struct MPContext*) ; 
 int /*<<< orphan*/  handle_update_cache (struct MPContext*) ; 
 int /*<<< orphan*/  handle_vo_events (struct MPContext*) ; 
 scalar_t__ mp_filter_has_failed (scalar_t__) ; 
 scalar_t__ mp_filter_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_process_input (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wait_events (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  update_core_idle_state (struct MPContext*) ; 
 int /*<<< orphan*/  update_demuxer_properties (struct MPContext*) ; 
 int /*<<< orphan*/  update_osd_msg (struct MPContext*) ; 
 int /*<<< orphan*/  update_subtitles (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_video (struct MPContext*) ; 

void run_playloop(struct MPContext *mpctx)
{
    if (encode_lavc_didfail(mpctx->encode_lavc_ctx)) {
        mpctx->stop_play = PT_QUIT;
        return;
    }

    update_demuxer_properties(mpctx);

    handle_cursor_autohide(mpctx);
    handle_vo_events(mpctx);
    handle_command_updates(mpctx);

    if (mpctx->lavfi && mp_filter_has_failed(mpctx->lavfi))
        mpctx->stop_play = AT_END_OF_FILE;

    fill_audio_out_buffers(mpctx);
    write_video(mpctx);

    handle_delayed_audio_seek(mpctx);

    handle_playback_restart(mpctx);

    handle_playback_time(mpctx);

    handle_dummy_ticks(mpctx);

    update_osd_msg(mpctx);
    if (mpctx->video_status == STATUS_EOF)
        update_subtitles(mpctx, mpctx->playback_pts);

    handle_eof(mpctx);

    handle_loop_file(mpctx);

    handle_keep_open(mpctx);

    handle_sstep(mpctx);

    update_core_idle_state(mpctx);

    if (mpctx->stop_play)
        return;

    handle_osd_redraw(mpctx);

    if (mp_filter_run(mpctx->filter_root))
        mp_wakeup_core(mpctx);
    mp_wait_events(mpctx);

    handle_update_cache(mpctx);

    mp_process_input(mpctx);

    handle_chapter_change(mpctx);

    handle_force_window(mpctx, false);

    execute_queued_seek(mpctx);
}