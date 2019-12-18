#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sival_int; } ;
struct TYPE_5__ {int si_syscall; TYPE_1__ si_value; } ;
typedef  TYPE_2__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int* kill_msg ; 
 int /*<<< orphan*/  strlen (int*) ; 
 int write (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_syssig(int signum, siginfo_t *si, void *thread_context) {
#if defined(si_syscall)
    int syscall_no = si->si_syscall;
#else
    // If system has no support for si_syscal, the information may not be
    // precise.
    int syscall_no = si->si_value.sival_int;
#endif

    // Replace the characters in the kill message with the syscall number. We
    // can't safely printf (even write is not really valid, but we're crashing
    // anyway).

    kill_msg[39] = (syscall_no / 100) % 10 + '0';
    kill_msg[40] = (syscall_no / 10) % 10 + '0';
    kill_msg[41] = syscall_no % 10 + '0';
    if (write(2, kill_msg, strlen(kill_msg)) == -1) {
        // An error occurred, but we can't do anything about it here. This check
        // is mostly to avoid the "ignoring return value of 'write'" error on
        // distributions with broken gcc (no "ignore via cast to void" support).
    }

    // We can't use the nice exit() version because it causes at_exit handlers
    // to be looked up and run. We can't take any locks while handling the
    // signal, so _exit() is the only thing to do safely.
    _exit(EXIT_FAILURE);
}