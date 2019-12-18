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
struct input_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  close_death_pipe () ; 
 int /*<<< orphan*/  close_tty () ; 
 int /*<<< orphan*/  death_pipe ; 
 int /*<<< orphan*/  getch2_enabled ; 
 struct input_ctx* input_ctx ; 
 int /*<<< orphan*/  input_thread ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_make_wakeup_pipe (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quit_request_sighandler ; 
 int read_terminal ; 
 int /*<<< orphan*/  setsigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  terminal_thread ; 
 int /*<<< orphan*/  tty_in ; 

void terminal_setup_getch(struct input_ctx *ictx)
{
    if (!getch2_enabled || input_ctx)
        return;

    if (mp_make_wakeup_pipe(death_pipe) < 0)
        return;

    // Disable reading from the terminal even if stdout is not a tty, to make
    //   mpv ... | less
    // do the right thing.
    read_terminal = isatty(tty_in) && isatty(STDOUT_FILENO);

    input_ctx = ictx;

    if (pthread_create(&input_thread, NULL, terminal_thread, NULL)) {
        input_ctx = NULL;
        close_death_pipe();
        close_tty();
        return;
    }

    setsigaction(SIGINT,  quit_request_sighandler, SA_RESETHAND, false);
    setsigaction(SIGQUIT, quit_request_sighandler, SA_RESETHAND, false);
    setsigaction(SIGTERM, quit_request_sighandler, SA_RESETHAND, false);
}