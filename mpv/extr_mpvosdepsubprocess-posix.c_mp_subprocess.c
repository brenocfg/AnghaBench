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
typedef  int /*<<< orphan*/  (* subprocess_read_cb ) (void*,char*,scalar_t__) ;
struct pollfd {int fd; scalar_t__ revents; int /*<<< orphan*/  events; } ;
struct mp_cancel {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  posix_spawn_file_actions_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MP_ARRAY_SIZE (struct pollfd*) ; 
 int MP_SUBPROCESS_EKILLED_BY_US ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  SAFE_CLOSE (int) ; 
 int /*<<< orphan*/  SIGKILL ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  environ ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int mp_cancel_get_fd (struct mp_cancel*) ; 
 scalar_t__ mp_make_cloexec_pipe (int*) ; 
 int open (char*,int) ; 
 scalar_t__ posix_spawn_file_actions_adddup2 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  posix_spawn_file_actions_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ posix_spawn_file_actions_init (int /*<<< orphan*/ *) ; 
 scalar_t__ posix_spawnp (int*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 scalar_t__ sparse_poll (struct pollfd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (void*,char*,scalar_t__) ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 

int mp_subprocess(char **args, struct mp_cancel *cancel, void *ctx,
                  subprocess_read_cb on_stdout, subprocess_read_cb on_stderr,
                  char **error)
{
    posix_spawn_file_actions_t fa;
    bool fa_destroy = false;
    int status = -1;
    int p_stdout[2] = {-1, -1};
    int p_stderr[2] = {-1, -1};
    int devnull = -1;
    pid_t pid = -1;
    bool spawned = false;
    bool killed_by_us = false;

    if (on_stdout && mp_make_cloexec_pipe(p_stdout) < 0)
        goto done;
    if (on_stderr && mp_make_cloexec_pipe(p_stderr) < 0)
        goto done;

    devnull = open("/dev/null", O_RDONLY | O_CLOEXEC);
    if (devnull < 0)
        goto done;

    if (posix_spawn_file_actions_init(&fa))
        goto done;
    fa_destroy = true;
    // redirect stdin/stdout/stderr
    if (posix_spawn_file_actions_adddup2(&fa, devnull, 0))
        goto done;
    if (p_stdout[1] >= 0 && posix_spawn_file_actions_adddup2(&fa, p_stdout[1], 1))
        goto done;
    if (p_stderr[1] >= 0 && posix_spawn_file_actions_adddup2(&fa, p_stderr[1], 2))
        goto done;

    if (posix_spawnp(&pid, args[0], &fa, NULL, args, environ)) {
        pid = -1;
        goto done;
    }
    spawned = true;

    SAFE_CLOSE(p_stdout[1]);
    SAFE_CLOSE(p_stderr[1]);
    SAFE_CLOSE(devnull);

    int *read_fds[2] = {&p_stdout[0], &p_stderr[0]};
    subprocess_read_cb read_cbs[2] = {on_stdout, on_stderr};

    while (p_stdout[0] >= 0 || p_stderr[0] >= 0) {
        struct pollfd fds[] = {
            {.events = POLLIN, .fd = *read_fds[0]},
            {.events = POLLIN, .fd = *read_fds[1]},
            {.events = POLLIN, .fd = cancel ? mp_cancel_get_fd(cancel) : -1},
        };
        if (sparse_poll(fds, MP_ARRAY_SIZE(fds), -1) < 0 && errno != EINTR)
            break;
        for (int n = 0; n < 2; n++) {
            if (fds[n].revents) {
                char buf[4096];
                ssize_t r = read(*read_fds[n], buf, sizeof(buf));
                if (r < 0 && errno == EINTR)
                    continue;
                if (r > 0 && read_cbs[n])
                    read_cbs[n](ctx, buf, r);
                if (r <= 0)
                    SAFE_CLOSE(*read_fds[n]);
            }
        }
        if (fds[2].revents) {
            kill(pid, SIGKILL);
            killed_by_us = true;
            break;
        }
    }

    // Note: it can happen that a child process closes the pipe, but does not
    //       terminate yet. In this case, we would have to run waitpid() in
    //       a separate thread and use pthread_cancel(), or use other weird
    //       and laborious tricks. So this isn't handled yet.
    while (waitpid(pid, &status, 0) < 0 && errno == EINTR) {}

done:
    if (fa_destroy)
        posix_spawn_file_actions_destroy(&fa);
    SAFE_CLOSE(p_stdout[0]);
    SAFE_CLOSE(p_stdout[1]);
    SAFE_CLOSE(p_stderr[0]);
    SAFE_CLOSE(p_stderr[1]);
    SAFE_CLOSE(devnull);

    if (!spawned || (WIFEXITED(status) && WEXITSTATUS(status) == 127)) {
        *error = "init";
        status = -1;
    } else if (WIFEXITED(status)) {
        *error = NULL;
        status = WEXITSTATUS(status);
    } else {
        *error = "killed";
        status = killed_by_us ? MP_SUBPROCESS_EKILLED_BY_US : -1;
    }

    return status;
}