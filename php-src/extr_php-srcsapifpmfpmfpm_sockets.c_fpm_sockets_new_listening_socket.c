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
struct sockaddr_un {char* sun_path; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct fpm_worker_pool_s {scalar_t__ listen_address_domain; int socket_mode; TYPE_1__* config; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  flags ;
struct TYPE_2__ {char* listen_address; int /*<<< orphan*/  listen_backlog; } ;

/* Variables and functions */
 scalar_t__ FPM_AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fpm_socket_unix_test_connect (struct sockaddr_un*,int) ; 
 scalar_t__ fpm_unix_set_socket_premissions (struct fpm_worker_pool_s*,char*) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int umask (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int fpm_sockets_new_listening_socket(struct fpm_worker_pool_s *wp, struct sockaddr *sa, int socklen) /* {{{ */
{
	int flags = 1;
	int sock;
	mode_t saved_umask = 0;

	sock = socket(sa->sa_family, SOCK_STREAM, 0);

	if (0 > sock) {
		zlog(ZLOG_SYSERROR, "failed to create new listening socket: socket()");
		return -1;
	}

	if (0 > setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags))) {
		zlog(ZLOG_WARNING, "failed to change socket attribute");
	}

	if (wp->listen_address_domain == FPM_AF_UNIX) {
		if (fpm_socket_unix_test_connect((struct sockaddr_un *)sa, socklen) == 0) {
			zlog(ZLOG_ERROR, "Another FPM instance seems to already listen on %s", ((struct sockaddr_un *) sa)->sun_path);
			close(sock);
			return -1;
		}
		unlink( ((struct sockaddr_un *) sa)->sun_path);
		saved_umask = umask(0777 ^ wp->socket_mode);
	}

	if (0 > bind(sock, sa, socklen)) {
		zlog(ZLOG_SYSERROR, "unable to bind listening socket for address '%s'", wp->config->listen_address);
		if (wp->listen_address_domain == FPM_AF_UNIX) {
			umask(saved_umask);
		}
		close(sock);
		return -1;
	}

	if (wp->listen_address_domain == FPM_AF_UNIX) {
		char *path = ((struct sockaddr_un *) sa)->sun_path;

		umask(saved_umask);

		if (0 > fpm_unix_set_socket_premissions(wp, path)) {
			close(sock);
			return -1;
		}
	}

	if (0 > listen(sock, wp->config->listen_backlog)) {
		zlog(ZLOG_SYSERROR, "failed to listen to address '%s'", wp->config->listen_address);
		close(sock);
		return -1;
	}

	return sock;
}