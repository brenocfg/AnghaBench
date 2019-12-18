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
struct target {int dummy; } ;
struct pid_stat {size_t fds_size; struct pid_fd* fds; struct target* group_target; struct target* user_target; struct target* target; int /*<<< orphan*/  updated; } ;
struct pid_fd {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  aggregate_fd_on_target (int,struct target*) ; 
 int all_files_size ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  reallocate_target_fds (struct target*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void aggregate_pid_fds_on_targets(struct pid_stat *p) {

    if(unlikely(!p->updated)) {
        // the process is not running
        return;
    }

    struct target *w = p->target, *u = p->user_target, *g = p->group_target;

    reallocate_target_fds(w);
    reallocate_target_fds(u);
    reallocate_target_fds(g);

    size_t c, size = p->fds_size;
    struct pid_fd *fds = p->fds;
    for(c = 0; c < size ;c++) {
        int fd = fds[c].fd;

        if(likely(fd <= 0 || fd >= all_files_size))
            continue;

        aggregate_fd_on_target(fd, w);
        aggregate_fd_on_target(fd, u);
        aggregate_fd_on_target(fd, g);
    }
}