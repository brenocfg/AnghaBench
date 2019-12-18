#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  tcp; } ;
typedef  TYPE_1__ fcgi_request ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 size_t INT_MAX ; 
 size_t UINT_MAX ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ errno ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static inline ssize_t safe_write(fcgi_request *req, const void *buf, size_t count)
{
	int    ret;
	size_t n = 0;

	do {
#ifdef _WIN32
		size_t tmp;
#endif
		errno = 0;
#ifdef _WIN32
		tmp = count - n;

		if (!req->tcp) {
			unsigned int out_len = tmp > UINT_MAX ? UINT_MAX : (unsigned int)tmp;

			ret = write(req->fd, ((char*)buf)+n, out_len);
		} else {
			int out_len = tmp > INT_MAX ? INT_MAX : (int)tmp;

			ret = send(req->fd, ((char*)buf)+n, out_len, 0);
			if (ret <= 0) {
				errno = WSAGetLastError();
			}
		}
#else
		ret = write(req->fd, ((char*)buf)+n, count-n);
#endif
		if (ret > 0) {
			n += ret;
		} else if (ret <= 0 && errno != 0 && errno != EINTR) {
			return ret;
		}
	} while (n != count);
	return n;
}