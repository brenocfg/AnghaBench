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
struct track {scalar_t__ dec; struct dec_sub* d_sub; } ;
struct m_config_option {int dummy; } ;
struct dec_sub {int dummy; } ;
struct command_ctx {void* cur_ipc_input; void* cur_ipc; } ;
struct MPOpts {void* input_file; void* ipc_path; } ;
struct MPContext {scalar_t__ video_out; int /*<<< orphan*/  global; int /*<<< orphan*/  clients; int /*<<< orphan*/  ipc_ctx; struct MPOpts* opts; int /*<<< orphan*/  input; struct track*** current_track; int /*<<< orphan*/  osd; struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int NUM_PTRACKS ; 
 size_t STREAM_SUB ; 
 size_t STREAM_VIDEO ; 
 int UPDATE_AUDIO ; 
 int UPDATE_BUILTIN_SCRIPTS ; 
 int UPDATE_IMGPAR ; 
 int UPDATE_INPUT ; 
 int UPDATE_LAVFI_COMPLEX ; 
 int UPDATE_OSD ; 
 int UPDATE_PRIORITY ; 
 int UPDATE_SCREENSAVER ; 
 int UPDATE_TERM ; 
 int UPDATE_VOL ; 
 int UPDATE_VO_RESIZE ; 
 int /*<<< orphan*/  VOCTRL_EXTERNAL_RESIZE ; 
 int /*<<< orphan*/  audio_update_volume (struct MPContext*) ; 
 int /*<<< orphan*/  bstr0 (void*) ; 
 int /*<<< orphan*/  bstr_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_decoder_wrapper_reset_params (scalar_t__) ; 
 int /*<<< orphan*/  mp_force_video_refresh (struct MPContext*) ; 
 int /*<<< orphan*/  mp_init_ipc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_update_opts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_load_builtin_scripts (struct MPContext*) ; 
 int /*<<< orphan*/  mp_uninit_ipc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_update_logging (struct MPContext*,int) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  osd_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_audio_output (struct MPContext*) ; 
 int /*<<< orphan*/  sub_update_opts (struct dec_sub*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_strdup (struct command_ctx*,void*) ; 
 int /*<<< orphan*/  update_lavfi_complex (struct MPContext*) ; 
 int /*<<< orphan*/  update_priority (struct MPContext*) ; 
 int /*<<< orphan*/  update_screensaver_state (struct MPContext*) ; 
 int /*<<< orphan*/  vo_control (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mp_option_change_callback(void *ctx, struct m_config_option *co, int flags)
{
    struct MPContext *mpctx = ctx;
    struct command_ctx *cmd = mpctx->command_ctx;

    if (flags & UPDATE_TERM)
        mp_update_logging(mpctx, false);

    if (flags & UPDATE_OSD) {
        for (int n = 0; n < NUM_PTRACKS; n++) {
            struct track *track = mpctx->current_track[n][STREAM_SUB];
            struct dec_sub *sub = track ? track->d_sub : NULL;
            if (sub)
                sub_update_opts(track->d_sub);
        }
        osd_changed(mpctx->osd);
        mp_wakeup_core(mpctx);
    }

    if (flags & UPDATE_BUILTIN_SCRIPTS)
        mp_load_builtin_scripts(mpctx);

    if (flags & UPDATE_IMGPAR) {
        struct track *track = mpctx->current_track[0][STREAM_VIDEO];
        if (track && track->dec) {
            mp_decoder_wrapper_reset_params(track->dec);
            mp_force_video_refresh(mpctx);
        }
    }

    if (flags & UPDATE_INPUT) {
        mp_input_update_opts(mpctx->input);

        // Rather coarse change-detection, but sufficient effort.
        struct MPOpts *opts = mpctx->opts;
        if (!bstr_equals(bstr0(cmd->cur_ipc), bstr0(opts->ipc_path)) ||
            !bstr_equals(bstr0(cmd->cur_ipc_input), bstr0(opts->input_file)))
        {
            talloc_free(cmd->cur_ipc);
            talloc_free(cmd->cur_ipc_input);
            cmd->cur_ipc = talloc_strdup(cmd, opts->ipc_path);
            cmd->cur_ipc_input = talloc_strdup(cmd, opts->input_file);
            mp_uninit_ipc(mpctx->ipc_ctx);
            mpctx->ipc_ctx = mp_init_ipc(mpctx->clients, mpctx->global);
        }
    }

    if (flags & UPDATE_AUDIO)
        reload_audio_output(mpctx);

    if (flags & UPDATE_PRIORITY)
        update_priority(mpctx);

    if (flags & UPDATE_SCREENSAVER)
        update_screensaver_state(mpctx);

    if (flags & UPDATE_VOL)
        audio_update_volume(mpctx);

    if (flags & UPDATE_LAVFI_COMPLEX)
        update_lavfi_complex(mpctx);

    if (flags & UPDATE_VO_RESIZE) {
        if (mpctx->video_out)
            vo_control(mpctx->video_out, VOCTRL_EXTERNAL_RESIZE, NULL);
    }
}