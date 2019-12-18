#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  off; int /*<<< orphan*/  fd; } ;
struct lwan_readahead_cmd {int cmd; TYPE_2__ madvise; TYPE_1__ readahead; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  IOPRIO_CLASS_IDLE ; 
 int /*<<< orphan*/  IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IOPRIO_WHO_PROCESS ; 
#define  MADVISE 130 
 int /*<<< orphan*/  MADV_WILLNEED ; 
#define  READAHEAD 129 
#define  SHUTDOWN 128 
 scalar_t__ UNLIKELY (size_t) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ioprio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_set_thread_name (char*) ; 
 int /*<<< orphan*/  lwan_status_perror (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_warning (char*,size_t) ; 
 int /*<<< orphan*/  madvise (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t read (int /*<<< orphan*/ ,struct lwan_readahead_cmd*,int) ; 
 int /*<<< orphan*/  readahead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * readahead_pipe_fd ; 

__attribute__((used)) static void *lwan_readahead_loop(void *data __attribute__((unused)))
{
    /* Idle priority for the calling thread.   Magic value of `7` obtained from
     * sample program in linux/Documentation/block/ioprio.txt.  This is a no-op
     * on anything but Linux.  */
    ioprio_set(IOPRIO_WHO_PROCESS, 0, IOPRIO_PRIO_VALUE(IOPRIO_CLASS_IDLE, 7));

    lwan_set_thread_name("readahead");

    while (true) {
        struct lwan_readahead_cmd cmd[16];
        ssize_t n_bytes = read(readahead_pipe_fd[0], cmd, sizeof(cmd));
        ssize_t cmds;

        if (UNLIKELY(n_bytes < 0)) {
            if (errno == EAGAIN || errno == EINTR)
                continue;
            lwan_status_perror("Ignoring error while reading from pipe (%d)",
                               readahead_pipe_fd[0]);
            continue;
#if PIPE_DIRECT_FLAG
        } else if (UNLIKELY(n_bytes % (ssize_t)sizeof(cmd[0]))) {
            lwan_status_warning("Ignoring readahead packet read of %zd bytes",
                                n_bytes);
            continue;
#endif
        }

        cmds = n_bytes / (ssize_t)sizeof(struct lwan_readahead_cmd);
        for (ssize_t i = 0; i < cmds; i++) {
            switch (cmd[i].cmd) {
            case READAHEAD:
                readahead(cmd[i].readahead.fd, cmd[i].readahead.off,
                          cmd[i].readahead.size);
                break;
            case MADVISE:
                madvise(cmd[i].madvise.addr, cmd[i].madvise.length,
                        MADV_WILLNEED);
                mlock(cmd[i].madvise.addr, cmd[i].madvise.length);
                break;
            case SHUTDOWN:
                goto out;
            }
        }
    }

out:
    return NULL;
}