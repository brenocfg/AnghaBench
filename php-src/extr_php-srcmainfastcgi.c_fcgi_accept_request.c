#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  scalar_t__ sa_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_6__ {int /*<<< orphan*/  (* on_read ) () ;int /*<<< orphan*/  (* on_accept ) () ;} ;
struct TYPE_7__ {int fd; int listen_socket; TYPE_1__ hook; } ;
typedef  TYPE_2__ fcgi_request ;

/* Variables and functions */
 scalar_t__ ECONNABORTED ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FCGI_ERROR ; 
 int /*<<< orphan*/  FCGI_LOCK (int) ; 
 int /*<<< orphan*/  FCGI_UNLOCK (int) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ client_sa ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcgi_close (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  fcgi_get_last_client_ip () ; 
 int /*<<< orphan*/  fcgi_is_allowed () ; 
 int /*<<< orphan*/  fcgi_log (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fcgi_read_request (TYPE_2__*) ; 
 scalar_t__ in_shutdown ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int fcgi_accept_request(fcgi_request *req)
{
#ifdef _WIN32
	HANDLE pipe;
	OVERLAPPED ov;
#endif

	while (1) {
		if (req->fd < 0) {
			while (1) {
				if (in_shutdown) {
					return -1;
				}
#ifdef _WIN32
				if (!req->tcp) {
					pipe = (HANDLE)_get_osfhandle(req->listen_socket);
					FCGI_LOCK(req->listen_socket);
					ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
					if (!ConnectNamedPipe(pipe, &ov)) {
						errno = GetLastError();
						if (errno == ERROR_IO_PENDING) {
							while (WaitForSingleObject(ov.hEvent, 1000) == WAIT_TIMEOUT) {
								if (in_shutdown) {
									CloseHandle(ov.hEvent);
									FCGI_UNLOCK(req->listen_socket);
									return -1;
								}
							}
						} else if (errno != ERROR_PIPE_CONNECTED) {
						}
					}
					CloseHandle(ov.hEvent);
					req->fd = req->listen_socket;
					FCGI_UNLOCK(req->listen_socket);
				} else {
					SOCKET listen_socket = (SOCKET)_get_osfhandle(req->listen_socket);
#else
				{
					int listen_socket = req->listen_socket;
#endif
					sa_t sa;
					socklen_t len = sizeof(sa);

					req->hook.on_accept();

					FCGI_LOCK(req->listen_socket);
					req->fd = accept(listen_socket, (struct sockaddr *)&sa, &len);
					FCGI_UNLOCK(req->listen_socket);

					client_sa = sa;
					if (req->fd >= 0 && !fcgi_is_allowed()) {
						fcgi_log(FCGI_ERROR, "Connection disallowed: IP address '%s' has been dropped.", fcgi_get_last_client_ip());
						closesocket(req->fd);
						req->fd = -1;
						continue;
					}
				}

#ifdef _WIN32
				if (req->fd < 0 && (in_shutdown || errno != EINTR)) {
#else
				if (req->fd < 0 && (in_shutdown || (errno != EINTR && errno != ECONNABORTED))) {
#endif
					return -1;
				}

#ifdef _WIN32
				break;
#else
				if (req->fd >= 0) {
#if defined(HAVE_POLL)
					struct pollfd fds;
					int ret;

					fds.fd = req->fd;
					fds.events = POLLIN;
					fds.revents = 0;
					do {
						errno = 0;
						ret = poll(&fds, 1, 5000);
					} while (ret < 0 && errno == EINTR);
					if (ret > 0 && (fds.revents & POLLIN)) {
						break;
					}
					fcgi_close(req, 1, 0);
#else
					if (req->fd < FD_SETSIZE) {
						struct timeval tv = {5,0};
						fd_set set;
						int ret;

						FD_ZERO(&set);
						FD_SET(req->fd, &set);
						do {
							errno = 0;
							ret = select(req->fd + 1, &set, NULL, NULL, &tv) >= 0;
						} while (ret < 0 && errno == EINTR);
						if (ret > 0 && FD_ISSET(req->fd, &set)) {
							break;
						}
						fcgi_close(req, 1, 0);
					} else {
						fcgi_log(FCGI_ERROR, "Too many open file descriptors. FD_SETSIZE limit exceeded.");
						fcgi_close(req, 1, 0);
					}
#endif
				}
#endif
			}
		} else if (in_shutdown) {
			return -1;
		}
		req->hook.on_read();
		if (fcgi_read_request(req)) {
#ifdef _WIN32
			if (is_impersonate && !req->tcp) {
				pipe = (HANDLE)_get_osfhandle(req->fd);
				if (!ImpersonateNamedPipeClient(pipe)) {
					fcgi_close(req, 1, 1);
					continue;
				}
			}
#endif
			return req->fd;
		} else {
			fcgi_close(req, 1, 1);
		}
	}
}