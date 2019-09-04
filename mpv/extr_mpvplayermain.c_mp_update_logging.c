#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct MPContext {int /*<<< orphan*/  input; TYPE_1__* opts; int /*<<< orphan*/  log; int /*<<< orphan*/  global; } ;
struct TYPE_2__ {int use_terminal; scalar_t__ consolecontrols; } ;

/* Variables and functions */
 int cas_terminal_owner (struct MPContext*,struct MPContext*) ; 
 int mp_msg_has_log_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_msg_update_msglevels (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_print_version (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  terminal_init () ; 
 int /*<<< orphan*/  terminal_setup_getch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminal_uninit () ; 

void mp_update_logging(struct MPContext *mpctx, bool preinit)
{
    bool had_log_file = mp_msg_has_log_file(mpctx->global);

    mp_msg_update_msglevels(mpctx->global, mpctx->opts);

    bool enable = mpctx->opts->use_terminal;
    bool enabled = cas_terminal_owner(mpctx, mpctx);
    if (enable != enabled) {
        if (enable && cas_terminal_owner(NULL, mpctx)) {
            terminal_init();
            enabled = true;
        } else if (!enable) {
            terminal_uninit();
            cas_terminal_owner(mpctx, NULL);
        }
    }

    if (mp_msg_has_log_file(mpctx->global) && !had_log_file)
        mp_print_version(mpctx->log, false); // for log-file=... in config files

    if (enabled && !preinit && mpctx->opts->consolecontrols)
        terminal_setup_getch(mpctx->input);
}