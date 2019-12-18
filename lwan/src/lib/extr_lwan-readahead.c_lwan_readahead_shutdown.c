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
struct lwan_readahead_cmd {int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lwan_status_debug (char*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* readahead_pipe_fd ; 
 int /*<<< orphan*/  readahead_self ; 
 int /*<<< orphan*/  write (int,struct lwan_readahead_cmd*,int) ; 

void lwan_readahead_shutdown(void)
{
    struct lwan_readahead_cmd cmd = {
        .cmd = SHUTDOWN,
    };

    if (readahead_pipe_fd[0] == readahead_pipe_fd[1] &&
        readahead_pipe_fd[0] == -1)
        return;

    lwan_status_debug("Shutting down readahead thread");

    write(readahead_pipe_fd[1], &cmd, sizeof(cmd));
    pthread_join(readahead_self, NULL);

    close(readahead_pipe_fd[0]);
    close(readahead_pipe_fd[1]);
    readahead_pipe_fd[0] = readahead_pipe_fd[1] = -1;
}