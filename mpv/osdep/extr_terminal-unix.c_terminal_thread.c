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
struct pollfd {scalar_t__ revents; int /*<<< orphan*/  fd; int /*<<< orphan*/  events; } ;
struct mp_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/ * death_pipe ; 
 int /*<<< orphan*/  getch2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getch2_poll () ; 
 int /*<<< orphan*/  input_ctx ; 
 struct mp_cmd* mp_input_parse_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_input_queue_cmd (int /*<<< orphan*/ ,struct mp_cmd*) ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 
 int /*<<< orphan*/  polldev (struct pollfd*,int,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int read_terminal ; 
 int /*<<< orphan*/  tty_in ; 

__attribute__((used)) static void *terminal_thread(void *ptr)
{
    mpthread_set_name("terminal");
    bool stdin_ok = read_terminal; // if false, we still wait for SIGTERM
    while (1) {
        getch2_poll();
        struct pollfd fds[2] = {
            { .events = POLLIN, .fd = death_pipe[0] },
            { .events = POLLIN, .fd = tty_in }
        };
        polldev(fds, stdin_ok ? 2 : 1, -1);
        if (fds[0].revents)
            break;
        if (fds[1].revents) {
            if (!getch2(input_ctx))
                break;
        }
    }
    char c;
    bool quit = read(death_pipe[0], &c, 1) == 1 && c == 1;
    // Important if we received SIGTERM, rather than regular quit.
    if (quit) {
        struct mp_cmd *cmd = mp_input_parse_cmd(input_ctx, bstr0("quit 4"), "");
        if (cmd)
            mp_input_queue_cmd(input_ctx, cmd);
    }
    return NULL;
}