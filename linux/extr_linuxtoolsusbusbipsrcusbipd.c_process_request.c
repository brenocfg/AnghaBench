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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int do_accept (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  recv_pdu (int) ; 

int process_request(int listenfd)
{
	pid_t childpid;
	int connfd;

	connfd = do_accept(listenfd);
	if (connfd < 0)
		return -1;
	childpid = fork();
	if (childpid == 0) {
		close(listenfd);
		recv_pdu(connfd);
		exit(0);
	}
	close(connfd);
	return 0;
}