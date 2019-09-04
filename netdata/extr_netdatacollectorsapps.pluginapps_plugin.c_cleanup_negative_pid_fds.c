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
struct pid_stat {size_t fds_size; struct pid_fd* fds; } ;
struct pid_fd {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_pid_fd (struct pid_fd*) ; 
 int /*<<< orphan*/  file_descriptor_not_used (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void cleanup_negative_pid_fds(struct pid_stat *p) {
    struct pid_fd *pfd = p->fds, *pfdend = &p->fds[p->fds_size];

    while(pfd < pfdend) {
        int fd = pfd->fd;

        if(unlikely(fd < 0)) {
            file_descriptor_not_used(-(fd));
            clear_pid_fd(pfd);
        }

        pfd++;
    }
}