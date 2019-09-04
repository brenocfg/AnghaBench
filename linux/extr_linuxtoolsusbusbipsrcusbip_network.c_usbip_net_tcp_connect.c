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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_net_set_keepalive (int) ; 
 int /*<<< orphan*/  usbip_net_set_nodelay (int) ; 

int usbip_net_tcp_connect(char *hostname, char *service)
{
	struct addrinfo hints, *res, *rp;
	int sockfd;
	int ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	/* get all possible addresses */
	ret = getaddrinfo(hostname, service, &hints, &res);
	if (ret < 0) {
		dbg("getaddrinfo: %s service %s: %s", hostname, service,
		    gai_strerror(ret));
		return ret;
	}

	/* try the addresses */
	for (rp = res; rp; rp = rp->ai_next) {
		sockfd = socket(rp->ai_family, rp->ai_socktype,
				rp->ai_protocol);
		if (sockfd < 0)
			continue;

		/* should set TCP_NODELAY for usbip */
		usbip_net_set_nodelay(sockfd);
		/* TODO: write code for heartbeat */
		usbip_net_set_keepalive(sockfd);

		if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

		close(sockfd);
	}

	freeaddrinfo(res);

	if (!rp)
		return EAI_SYSTEM;

	return sockfd;
}