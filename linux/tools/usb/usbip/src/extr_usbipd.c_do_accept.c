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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  host ;

/* Variables and functions */
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getnameinfo (struct sockaddr*,int,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  info (char*,char*,...) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int tcpd_auth (int) ; 

__attribute__((used)) static int do_accept(int listenfd)
{
	int connfd;
	struct sockaddr_storage ss;
	socklen_t len = sizeof(ss);
	char host[NI_MAXHOST], port[NI_MAXSERV];
	int rc;

	memset(&ss, 0, sizeof(ss));

	connfd = accept(listenfd, (struct sockaddr *)&ss, &len);
	if (connfd < 0) {
		err("failed to accept connection");
		return -1;
	}

	rc = getnameinfo((struct sockaddr *)&ss, len, host, sizeof(host),
			 port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV);
	if (rc)
		err("getnameinfo: %s", gai_strerror(rc));

#ifdef HAVE_LIBWRAP
	rc = tcpd_auth(connfd);
	if (rc < 0) {
		info("denied access from %s", host);
		close(connfd);
		return -1;
	}
#endif
	info("connection from %s:%s", host, port);

	return connfd;
}