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

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  build_rcv_fd (int,int,int*,int,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test (int*,int,int,int,int) ; 

__attribute__((used)) static void run_one_test(int fam_send, int fam_rcv, int proto,
			 const char *addr_str)
{
	/* Below we test that a socket listening on a specific address
	 * is always selected in preference over a socket listening
	 * on addr_any. Bugs where this is not the case often result
	 * in sockets created first or last to get picked. So below
	 * we make sure that there are always addr_any sockets created
	 * before and after a specific socket is created.
	 */
	int rcv_fds[10], i;

	build_rcv_fd(AF_INET, proto, rcv_fds, 2, NULL);
	build_rcv_fd(AF_INET6, proto, rcv_fds + 2, 2, NULL);
	build_rcv_fd(fam_rcv, proto, rcv_fds + 4, 1, addr_str);
	build_rcv_fd(AF_INET, proto, rcv_fds + 5, 2, NULL);
	build_rcv_fd(AF_INET6, proto, rcv_fds + 7, 2, NULL);
	test(rcv_fds, 9, fam_send, proto, rcv_fds[4]);
	for (i = 0; i < 9; ++i)
		close(rcv_fds[i]);
	fprintf(stderr, "pass\n");
}