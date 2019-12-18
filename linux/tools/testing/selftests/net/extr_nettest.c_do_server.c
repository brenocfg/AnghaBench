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
struct timeval {scalar_t__ tv_sec; } ;
struct sockaddr_in6 {int dummy; } ;
struct sock_args {scalar_t__ type; scalar_t__ password; scalar_t__ bind_test_only; scalar_t__ has_grp; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCK_STREAM ; 
 int accept (int,void*,int*) ; 
 int check_device (int,struct sock_args*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  interactive ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  log_msg (char*) ; 
 int lsock_init (struct sock_args*) ; 
 int msg_loop (int /*<<< orphan*/ ,int,void*,int,struct sock_args*) ; 
 int msock_server (struct sock_args*) ; 
 scalar_t__ prog_timeout ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int show_sockstat (int,struct sock_args*) ; 
 scalar_t__ tcp_md5_remote (int,struct sock_args*) ; 

__attribute__((used)) static int do_server(struct sock_args *args)
{
	struct timeval timeout = { .tv_sec = prog_timeout }, *ptval = NULL;
	unsigned char addr[sizeof(struct sockaddr_in6)] = {};
	socklen_t alen = sizeof(addr);
	int lsd, csd = -1;

	fd_set rfds;
	int rc;

	if (prog_timeout)
		ptval = &timeout;

	if (args->has_grp)
		lsd = msock_server(args);
	else
		lsd = lsock_init(args);

	if (lsd < 0)
		return 1;

	if (args->bind_test_only) {
		close(lsd);
		return 0;
	}

	if (args->type != SOCK_STREAM) {
		rc = msg_loop(0, lsd, (void *) addr, alen, args);
		close(lsd);
		return rc;
	}

	if (args->password && tcp_md5_remote(lsd, args)) {
		close(lsd);
		return -1;
	}

	while (1) {
		log_msg("\n");
		log_msg("waiting for client connection.\n");
		FD_ZERO(&rfds);
		FD_SET(lsd, &rfds);

		rc = select(lsd+1, &rfds, NULL, NULL, ptval);
		if (rc == 0) {
			rc = 2;
			break;
		}

		if (rc < 0) {
			if (errno == EINTR)
				continue;

			log_err_errno("select failed");
			break;
		}

		if (FD_ISSET(lsd, &rfds)) {

			csd = accept(lsd, (void *) addr, &alen);
			if (csd < 0) {
				log_err_errno("accept failed");
				break;
			}

			rc = show_sockstat(csd, args);
			if (rc)
				break;

			rc = check_device(csd, args);
			if (rc)
				break;
		}

		rc = msg_loop(0, csd, (void *) addr, alen, args);
		close(csd);

		if (!interactive)
			break;
	}

	close(lsd);

	return rc;
}