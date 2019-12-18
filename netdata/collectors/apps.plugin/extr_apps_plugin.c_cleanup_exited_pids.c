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
struct pid_stat {int keep; scalar_t__ keeploops; size_t fds_size; struct pid_stat* next; int /*<<< orphan*/  pid; TYPE_1__* fds; int /*<<< orphan*/  comm; int /*<<< orphan*/  updated; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_pid_fd (TYPE_1__*) ; 
 scalar_t__ debug_enabled ; 
 int /*<<< orphan*/  debug_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_pid_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_descriptor_not_used (scalar_t__) ; 
 struct pid_stat* root_of_pids ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cleanup_exited_pids(void) {
    size_t c;
    struct pid_stat *p = NULL;

    for(p = root_of_pids; p ;) {
        if(!p->updated && (!p->keep || p->keeploops > 0)) {
            if(unlikely(debug_enabled && (p->keep || p->keeploops)))
                debug_log(" > CLEANUP cannot keep exited process %d (%s) anymore - removing it.", p->pid, p->comm);

            for(c = 0; c < p->fds_size; c++)
                if(p->fds[c].fd > 0) {
                    file_descriptor_not_used(p->fds[c].fd);
                    clear_pid_fd(&p->fds[c]);
                }

            pid_t r = p->pid;
            p = p->next;
            del_pid_entry(r);
        }
        else {
            if(unlikely(p->keep)) p->keeploops++;
            p->keep = 0;
            p = p->next;
        }
    }
}