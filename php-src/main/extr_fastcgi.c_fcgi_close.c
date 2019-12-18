#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* on_close ) () ;} ;
struct TYPE_5__ {int fd; TYPE_1__ hook; scalar_t__ nodelay; int /*<<< orphan*/  tcp; int /*<<< orphan*/  keep; scalar_t__ has_env; int /*<<< orphan*/  env; } ;
typedef  TYPE_2__ fcgi_request ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DisconnectNamedPipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushFileBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RevertToSelf () ; 
 int /*<<< orphan*/  _get_osfhandle (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  fcgi_hash_clean (int /*<<< orphan*/ *) ; 
 scalar_t__ is_impersonate ; 
 scalar_t__ recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int,int) ; 
 int /*<<< orphan*/  stub1 () ; 

void fcgi_close(fcgi_request *req, int force, int destroy)
{
	if (destroy && req->has_env) {
		fcgi_hash_clean(&req->env);
		req->has_env = 0;
	}

#ifdef _WIN32
	if (is_impersonate && !req->tcp) {
		RevertToSelf();
	}
#endif

	if ((force || !req->keep) && req->fd >= 0) {
#ifdef _WIN32
		if (!req->tcp) {
			HANDLE pipe = (HANDLE)_get_osfhandle(req->fd);

			if (!force) {
				FlushFileBuffers(pipe);
			}
			DisconnectNamedPipe(pipe);
		} else {
			if (!force) {
				char buf[8];

				shutdown(req->fd, 1);
				/* read any remaining data, it may be omitted */
				while (recv(req->fd, buf, sizeof(buf), 0) > 0) {}
			}
			closesocket(req->fd);
		}
#else
		if (!force) {
			char buf[8];

			shutdown(req->fd, 1);
			/* read any remaining data, it may be omitted */
			while (recv(req->fd, buf, sizeof(buf), 0) > 0) {}
		}
		close(req->fd);
#endif
#ifdef TCP_NODELAY
		req->nodelay = 0;
#endif
		req->fd = -1;

		req->hook.on_close();
	}
}