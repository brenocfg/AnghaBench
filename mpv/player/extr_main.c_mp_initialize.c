#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct MPOpts {int operation_mode; int force_vo; TYPE_1__* encode_opts; int /*<<< orphan*/  player_idle_mode; scalar_t__* test_mode; int /*<<< orphan*/  verbose; } ;
struct MPContext {int initialized; int /*<<< orphan*/  input; TYPE_2__* mconfig; int /*<<< orphan*/  encode_lavc_ctx; int /*<<< orphan*/  global; int /*<<< orphan*/  clients; int /*<<< orphan*/  log; TYPE_5__* playlist; struct MPOpts* opts; } ;
typedef  int /*<<< orphan*/  mpv_handle ;
struct TYPE_8__ {int /*<<< orphan*/  first; } ;
struct TYPE_7__ {struct MPContext* option_change_callback_ctx; int /*<<< orphan*/  (* option_change_callback ) (struct MPContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;struct MPContext* option_set_callback_cb; int /*<<< orphan*/  option_set_callback; } ;
struct TYPE_6__ {scalar_t__* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct MPContext*,char*) ; 
 int /*<<< orphan*/  MP_INFO (struct MPContext*,char*,...) ; 
 int /*<<< orphan*/  MP_INPUT_EXCLUSIVE ; 
 int /*<<< orphan*/  MP_STATS (struct MPContext*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct MPContext*,char*) ; 
 int /*<<< orphan*/  MSGL_FATAL ; 
 int M_OPT_EXIT ; 
 int /*<<< orphan*/  M_SETOPT_NO_OVERWRITE ; 
 int /*<<< orphan*/  UPDATE_OPTS_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cocoa_set_mpv_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_lavc_init (int /*<<< orphan*/ ) ; 
 scalar_t__ handle_force_window (struct MPContext*,int) ; 
 scalar_t__ handle_help_options (struct MPContext*) ; 
 int m_config_parse_mp_command_line (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  m_config_preparse_command_line (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  m_config_set_profile (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_get_resume_defaults (struct MPContext*) ; 
 int /*<<< orphan*/  mp_help_text ; 
 int /*<<< orphan*/  mp_init_paths (int /*<<< orphan*/ ,struct MPOpts*) ; 
 int /*<<< orphan*/  mp_input_enable_section (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_load_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_load_scripts (struct MPContext*) ; 
 int /*<<< orphan*/ * mp_new_client (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_null_log ; 
 int /*<<< orphan*/  mp_on_set_option ; 
 int /*<<< orphan*/  mp_option_change_callback (struct MPContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_parse_cfgfiles (struct MPContext*) ; 
 int /*<<< orphan*/  mp_print_version (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_update_logging (struct MPContext*,int) ; 
 int /*<<< orphan*/  print_libav_versions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ run_tests (struct MPContext*) ; 

int mp_initialize(struct MPContext *mpctx, char **options)
{
    struct MPOpts *opts = mpctx->opts;

    assert(!mpctx->initialized);

    // Preparse the command line, so we can init the terminal early.
    if (options) {
        m_config_preparse_command_line(mpctx->mconfig, mpctx->global,
                                       &opts->verbose, options);
    }

    mp_init_paths(mpctx->global, opts);
    mp_update_logging(mpctx, true);

    if (options) {
        MP_VERBOSE(mpctx, "Command line options:");
        for (int i = 0; options[i]; i++)
            MP_VERBOSE(mpctx, " '%s'", options[i]);
        MP_VERBOSE(mpctx, "\n");
    }

    mp_print_version(mpctx->log, false);

    mp_parse_cfgfiles(mpctx);

    if (options) {
        int r = m_config_parse_mp_command_line(mpctx->mconfig, mpctx->playlist,
                                               mpctx->global, options);
        if (r < 0)
            return r == M_OPT_EXIT ? 1 : -1;
    }

    if (opts->operation_mode == 1) {
        m_config_set_profile(mpctx->mconfig, "builtin-pseudo-gui",
                             M_SETOPT_NO_OVERWRITE);
        m_config_set_profile(mpctx->mconfig, "pseudo-gui", 0);
    }

    mp_get_resume_defaults(mpctx);

    mp_input_load_config(mpctx->input);

    // From this point on, all mpctx members are initialized.
    mpctx->initialized = true;
    mpctx->mconfig->option_set_callback = mp_on_set_option;
    mpctx->mconfig->option_set_callback_cb = mpctx;
    mpctx->mconfig->option_change_callback = mp_option_change_callback;
    mpctx->mconfig->option_change_callback_ctx = mpctx;
    // Run all update handlers.
    mp_option_change_callback(mpctx, NULL, UPDATE_OPTS_MASK);

    if (handle_help_options(mpctx))
        return 1; // help

    if (!print_libav_versions(mp_null_log, 0)) {
        print_libav_versions(mpctx->log, MSGL_FATAL);
        MP_FATAL(mpctx, "\nmpv was compiled against an incompatible version of "
                 "FFmpeg/Libav than the shared\nlibrary it is linked against. "
                 "This is most likely a broken build and could\nresult in "
                 "misbehavior and crashes.\n\nThis is a broken build.\n");
        return -1;
    }

#if HAVE_TESTS
    if (opts->test_mode && opts->test_mode[0])
        return run_tests(mpctx) ? 1 : -1;
#endif

    if (!mpctx->playlist->first && !opts->player_idle_mode) {
        // nothing to play
        mp_print_version(mpctx->log, true);
        MP_INFO(mpctx, "%s", mp_help_text);
        return 1;
    }

    MP_STATS(mpctx, "start init");

#if HAVE_COCOA
    mpv_handle *ctx = mp_new_client(mpctx->clients, "osx");
    cocoa_set_mpv_handle(ctx);
#endif

    if (opts->encode_opts->file && opts->encode_opts->file[0]) {
        mpctx->encode_lavc_ctx = encode_lavc_init(mpctx->global);
        if(!mpctx->encode_lavc_ctx) {
            MP_INFO(mpctx, "Encoding initialization failed.\n");
            return -1;
        }
        m_config_set_profile(mpctx->mconfig, "encoding", 0);
        mp_input_enable_section(mpctx->input, "encode", MP_INPUT_EXCLUSIVE);
    }

#if !HAVE_LIBASS
    MP_WARN(mpctx, "Compiled without libass.\n");
    MP_WARN(mpctx, "There will be no OSD and no text subtitles.\n");
#endif

    mp_load_scripts(mpctx);

    if (opts->force_vo == 2 && handle_force_window(mpctx, false) < 0)
        return -1;

    MP_STATS(mpctx, "end init");

    return 0;
}