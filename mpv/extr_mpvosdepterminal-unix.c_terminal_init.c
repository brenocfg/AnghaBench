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

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ STDIN_FILENO ; 
 scalar_t__ STDOUT_FILENO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  continue_sighandler ; 
 int getch2_enabled ; 
 int /*<<< orphan*/  getch2_poll () ; 
 scalar_t__ open (char*,int) ; 
 int /*<<< orphan*/  setsigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_sighandler ; 
 scalar_t__ tty_in ; 
 scalar_t__ tty_out ; 

void terminal_init(void)
{
    assert(!getch2_enabled);
    getch2_enabled = 1;

    tty_in = tty_out = open("/dev/tty", O_RDWR | O_CLOEXEC);
    if (tty_in < 0) {
        tty_in = STDIN_FILENO;
        tty_out = STDOUT_FILENO;
    }

    // handlers to fix terminal settings
    setsigaction(SIGCONT, continue_sighandler, 0, true);
    setsigaction(SIGTSTP, stop_sighandler, SA_RESETHAND, false);
    setsigaction(SIGTTIN, SIG_IGN, 0, true);
    setsigaction(SIGTTOU, SIG_IGN, 0, true);

    getch2_poll();
}