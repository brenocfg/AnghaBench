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
struct pid_stat {struct pid_fd* fds; } ;
struct pid_fd {int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_pid_fd (struct pid_fd*) ; 

__attribute__((used)) static inline void init_pid_fds(struct pid_stat *p, size_t first, size_t size) {
    struct pid_fd *pfd = &p->fds[first], *pfdend = &p->fds[first + size];
    size_t i = first;

    while(pfd < pfdend) {
#ifndef __FreeBSD__
        pfd->filename = NULL;
#endif
        clear_pid_fd(pfd);
        pfd++;
        i++;
    }
}