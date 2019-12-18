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
struct plugind {int obsolete; scalar_t__ pid; scalar_t__ enabled; } ;
typedef  int /*<<< orphan*/  (* siginfo_t ) (char*,scalar_t__) ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 int /*<<< orphan*/  P_PID ; 
 int /*<<< orphan*/  WEXITED ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int killpid (scalar_t__) ; 
 int /*<<< orphan*/  waitid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*,scalar_t__),int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pluginsd_worker_thread_cleanup(void *arg) {
    struct plugind *cd = (struct plugind *)arg;

    if(cd->enabled && !cd->obsolete) {
        cd->obsolete = 1;

        info("data collection thread exiting");

        if (cd->pid) {
            siginfo_t info;
            info("killing child process pid %d", cd->pid);
            if (killpid(cd->pid) != -1) {
                info("waiting for child process pid %d to exit...", cd->pid);
                waitid(P_PID, (id_t) cd->pid, &info, WEXITED);
            }
            cd->pid = 0;
        }
    }
}