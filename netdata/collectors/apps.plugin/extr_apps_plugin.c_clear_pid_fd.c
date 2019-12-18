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
struct pid_fd {scalar_t__ cache_iterations_reset; scalar_t__ cache_iterations_counter; scalar_t__ inode; scalar_t__ link_hash; scalar_t__ fd; } ;

/* Variables and functions */

__attribute__((used)) static inline void clear_pid_fd(struct pid_fd *pfd) {
    pfd->fd = 0;

    #ifndef __FreeBSD__
    pfd->link_hash = 0;
    pfd->inode = 0;
    pfd->cache_iterations_counter = 0;
    pfd->cache_iterations_reset = 0;
#endif
}