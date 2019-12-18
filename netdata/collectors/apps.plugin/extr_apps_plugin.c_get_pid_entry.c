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
struct pid_stat {int fds_size; size_t pid; struct pid_stat* next; struct pid_stat* prev; int /*<<< orphan*/  fds; } ;
struct pid_fd {int dummy; } ;
typedef  size_t pid_t ;

/* Variables and functions */
 int MAX_SPARE_FDS ; 
 struct pid_stat** all_pids ; 
 int /*<<< orphan*/  all_pids_count ; 
 struct pid_stat* callocz (int,int) ; 
 int /*<<< orphan*/  init_pid_fds (struct pid_stat*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (struct pid_stat*) ; 
 int /*<<< orphan*/  mallocz (int) ; 
 struct pid_stat* root_of_pids ; 
 scalar_t__ unlikely (struct pid_stat*) ; 

__attribute__((used)) static inline struct pid_stat *get_pid_entry(pid_t pid) {
    if(unlikely(all_pids[pid]))
        return all_pids[pid];

    struct pid_stat *p = callocz(sizeof(struct pid_stat), 1);
    p->fds = mallocz(sizeof(struct pid_fd) * MAX_SPARE_FDS);
    p->fds_size = MAX_SPARE_FDS;
    init_pid_fds(p, 0, p->fds_size);

    if(likely(root_of_pids))
        root_of_pids->prev = p;

    p->next = root_of_pids;
    root_of_pids = p;

    p->pid = pid;

    all_pids[pid] = p;
    all_pids_count++;

    return p;
}