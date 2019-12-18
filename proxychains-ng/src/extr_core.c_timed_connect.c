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
struct sockaddr {int dummy; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PDEBUG (char*,int) ; 
 int /*<<< orphan*/  PFUNC () ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll_retry (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_connect_time_out ; 
 int true_connect (int,struct sockaddr const*,int) ; 

__attribute__((used)) static int timed_connect(int sock, const struct sockaddr *addr, socklen_t len) {
	int ret, value;
	socklen_t value_len;
	struct pollfd pfd[1];
	PFUNC();

	pfd[0].fd = sock;
	pfd[0].events = POLLOUT;
	fcntl(sock, F_SETFL, O_NONBLOCK);
	ret = true_connect(sock, addr, len);
	PDEBUG("\nconnect ret=%d\n", ret);
	
	if(ret == -1 && errno == EINPROGRESS) {
		ret = poll_retry(pfd, 1, tcp_connect_time_out);
		PDEBUG("\npoll ret=%d\n", ret);
		if(ret == 1) {
			value_len = sizeof(socklen_t);
			getsockopt(sock, SOL_SOCKET, SO_ERROR, &value, &value_len);
			PDEBUG("\nvalue=%d\n", value);
			if(!value)
				ret = 0;
			else
				ret = -1;
		} else {
			ret = -1;
		}
	} else {
#ifdef DEBUG
		if(ret == -1)
			perror("true_connect");
#endif
		if(ret != 0)
			ret = -1;
	}

	fcntl(sock, F_SETFL, !O_NONBLOCK);
	return ret;
}