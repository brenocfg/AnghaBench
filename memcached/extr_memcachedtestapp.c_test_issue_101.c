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
struct conn {scalar_t__ sock; int (* write ) (struct conn*,char const*,size_t) ;} ;
typedef  int ssize_t ;
typedef  scalar_t__ pid_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
#define  EINTR 130 
#define  ENOMEM 129 
#define  EWOULDBLOCK 128 
 int /*<<< orphan*/  SIGTERM ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int TEST_SKIP ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 void* con ; 
 void* connect_server (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_ssl ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (struct conn*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  server_pid ; 
 int /*<<< orphan*/  start_server (int /*<<< orphan*/ *,int,int) ; 
 size_t strlen (char const*) ; 
 int stub1 (struct conn*,char const*,size_t) ; 
 int test_binary_noop () ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_issue_101(void) {
    enum { max = 2 };
    enum test_return ret = TEST_PASS;
    struct conn *conns[max];
    int ii = 0;
    pid_t child = 0;

    if (getenv("SKIP_TEST_101") != NULL) {
        return TEST_SKIP;
    }

    const char *command = "stats\r\nstats\r\nstats\r\nstats\r\nstats\r\n";
    size_t cmdlen = strlen(command);

    server_pid = start_server(&port, false, 1000);

    for (ii = 0; ii < max; ++ii) {
        conns[ii] = NULL;
        conns[ii] = connect_server("127.0.0.1", port, true, enable_ssl);
        assert(conns[ii]->sock > 0);
    }

    /* Send command on the connection until it blocks */
    for (ii = 0; ii < max; ++ii) {
        bool more = true;
        do {
            ssize_t err = conns[ii]->write(conns[ii], command, cmdlen);
            if (err == -1) {
                switch (errno) {
                case EINTR:
                    break;
                case ENOMEM:
                case EWOULDBLOCK:
                    more = false;
                    break;
                default:
                    ret = TEST_FAIL;
                    goto cleanup;
                }
            }
        } while (more);
    }

    child = fork();
    if (child == (pid_t)-1) {
        abort();
    } else if (child > 0) {
        int stat;
        pid_t c;
        while ((c = waitpid(child, &stat, 0)) == (pid_t)-1 && errno == EINTR);
        assert(c == child);
        assert(stat == 0);
    } else {
        con = connect_server("127.0.0.1", port, false, enable_ssl);
        ret = test_binary_noop();
        exit(0);
    }

 cleanup:
    /* close all connections */
    for (ii = 0; ii < max; ++ii) {
        struct conn *c = conns[ii];
        if (c == NULL) continue;
#ifdef TLS
        if (c->ssl) {
            SSL_shutdown(c->ssl);
            SSL_free(c->ssl);
        }
        if (c->ssl_ctx)
            SSL_CTX_free(c->ssl_ctx);
#endif
        if (c->sock > 0) close(c->sock);
        free(conns[ii]);
        conns[ii] = NULL;
    }

    assert(kill(server_pid, SIGTERM) == 0);

    return ret;
}