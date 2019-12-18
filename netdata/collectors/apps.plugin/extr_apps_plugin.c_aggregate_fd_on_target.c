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
struct target {int* target_fds; int /*<<< orphan*/  openother; int /*<<< orphan*/  openeventpolls; int /*<<< orphan*/  opensignalfds; int /*<<< orphan*/  opentimerfds; int /*<<< orphan*/  openeventfds; int /*<<< orphan*/  openinotifies; int /*<<< orphan*/  opensockets; int /*<<< orphan*/  openpipes; int /*<<< orphan*/  openfiles; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  FILETYPE_EVENTFD 136 
#define  FILETYPE_EVENTPOLL 135 
#define  FILETYPE_FILE 134 
#define  FILETYPE_INOTIFY 133 
#define  FILETYPE_OTHER 132 
#define  FILETYPE_PIPE 131 
#define  FILETYPE_SIGNALFD 130 
#define  FILETYPE_SOCKET 129 
#define  FILETYPE_TIMERFD 128 
 TYPE_1__* all_files ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void aggregate_fd_on_target(int fd, struct target *w) {
    if(unlikely(!w))
        return;

    if(unlikely(w->target_fds[fd])) {
        // it is already aggregated
        // just increase its usage counter
        w->target_fds[fd]++;
        return;
    }

    // increase its usage counter
    // so that we will not add it again
    w->target_fds[fd]++;

    switch(all_files[fd].type) {
        case FILETYPE_FILE:
            w->openfiles++;
            break;

        case FILETYPE_PIPE:
            w->openpipes++;
            break;

        case FILETYPE_SOCKET:
            w->opensockets++;
            break;

        case FILETYPE_INOTIFY:
            w->openinotifies++;
            break;

        case FILETYPE_EVENTFD:
            w->openeventfds++;
            break;

        case FILETYPE_TIMERFD:
            w->opentimerfds++;
            break;

        case FILETYPE_SIGNALFD:
            w->opensignalfds++;
            break;

        case FILETYPE_EVENTPOLL:
            w->openeventpolls++;
            break;

        case FILETYPE_OTHER:
            w->openother++;
            break;
    }
}