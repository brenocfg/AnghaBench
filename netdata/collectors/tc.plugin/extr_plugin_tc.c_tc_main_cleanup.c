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
struct netdata_static_thread {int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  (* siginfo_t ) (char*,scalar_t__) ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDATA_MAIN_THREAD_EXITED ; 
 int /*<<< orphan*/  NETDATA_MAIN_THREAD_EXITING ; 
 int /*<<< orphan*/  P_PID ; 
 int /*<<< orphan*/  WEXITED ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int killpid (scalar_t__) ; 
 scalar_t__ tc_child_pid ; 
 int /*<<< orphan*/  waitid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*,scalar_t__),int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc_main_cleanup(void *ptr) {
    struct netdata_static_thread *static_thread = (struct netdata_static_thread *)ptr;
    static_thread->enabled = NETDATA_MAIN_THREAD_EXITING;

    info("cleaning up...");

    if(tc_child_pid) {
        info("TC: killing with SIGTERM tc-qos-helper process %d", tc_child_pid);
        if(killpid(tc_child_pid) != -1) {
            siginfo_t info;

            info("TC: waiting for tc plugin child process pid %d to exit...", tc_child_pid);
            waitid(P_PID, (id_t) tc_child_pid, &info, WEXITED);
        }

        tc_child_pid = 0;
    }

    static_thread->enabled = NETDATA_MAIN_THREAD_EXITED;
}