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
struct tcp_server_args {unsigned short port; int /*<<< orphan*/ * ctl; } ;
typedef  int /*<<< orphan*/  err ;

/* Variables and functions */
 int EADDRINUSE ; 
 int KSFT_FAIL ; 
 int KSFT_PASS ; 
 int KSFT_SKIP ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 char* cg_name (char const*,char*) ; 
 scalar_t__ cg_read_key_long (char*,char*,char*) ; 
 scalar_t__ cg_read_long (char*,char*) ; 
 int cg_run_nowait (char*,int /*<<< orphan*/ ,struct tcp_server_args*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ pipe (int /*<<< orphan*/ *) ; 
 int rand () ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int tcp_client (char*,unsigned short) ; 
 int /*<<< orphan*/  tcp_server ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_memcg_sock(const char *root)
{
	int bind_retries = 5, ret = KSFT_FAIL, pid, err;
	unsigned short port;
	char *memcg;

	memcg = cg_name(root, "memcg_test");
	if (!memcg)
		goto cleanup;

	if (cg_create(memcg))
		goto cleanup;

	while (bind_retries--) {
		struct tcp_server_args args;

		if (pipe(args.ctl))
			goto cleanup;

		port = args.port = 1000 + rand() % 60000;

		pid = cg_run_nowait(memcg, tcp_server, &args);
		if (pid < 0)
			goto cleanup;

		close(args.ctl[1]);
		if (read(args.ctl[0], &err, sizeof(err)) != sizeof(err))
			goto cleanup;
		close(args.ctl[0]);

		if (!err)
			break;
		if (err != EADDRINUSE)
			goto cleanup;

		waitpid(pid, NULL, 0);
	}

	if (err == EADDRINUSE) {
		ret = KSFT_SKIP;
		goto cleanup;
	}

	if (tcp_client(memcg, port) != KSFT_PASS)
		goto cleanup;

	waitpid(pid, &err, 0);
	if (WEXITSTATUS(err))
		goto cleanup;

	if (cg_read_long(memcg, "memory.current") < 0)
		goto cleanup;

	if (cg_read_key_long(memcg, "memory.stat", "sock "))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	free(memcg);

	return ret;
}