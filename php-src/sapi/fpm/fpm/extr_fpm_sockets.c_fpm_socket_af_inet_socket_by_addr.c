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
struct fpm_worker_pool_s {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  fpm_get_in_addr (int /*<<< orphan*/ ) ; 
 int fpm_sockets_get_listening_socket (struct fpm_worker_pool_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int fpm_socket_af_inet_socket_by_addr(struct fpm_worker_pool_s *wp, const char *addr, const char *port) /* {{{ */
{
	struct addrinfo hints, *servinfo, *p;
	char tmpbuf[INET6_ADDRSTRLEN];
	int status;
	int sock = -1;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(addr, port, &hints, &servinfo)) != 0) {
		zlog(ZLOG_ERROR, "getaddrinfo: %s\n", gai_strerror(status));
		return -1;
	}

	for (p = servinfo; p != NULL; p = p->ai_next) {
		inet_ntop(p->ai_family, fpm_get_in_addr(p->ai_addr), tmpbuf, INET6_ADDRSTRLEN);
		if (sock < 0) {
			if ((sock = fpm_sockets_get_listening_socket(wp, p->ai_addr, p->ai_addrlen)) != -1) {
				zlog(ZLOG_DEBUG, "Found address for %s, socket opened on %s", addr, tmpbuf);
			}
		} else {
			zlog(ZLOG_WARNING, "Found multiple addresses for %s, %s ignored", addr, tmpbuf);
		}
	}

	freeaddrinfo(servinfo);

	return sock;
}