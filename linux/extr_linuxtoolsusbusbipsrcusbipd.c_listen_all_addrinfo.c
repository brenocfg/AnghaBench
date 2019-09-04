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

/* Variables and functions */
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  addrinfo_to_text (struct addrinfo*,char*,size_t const) ; 
 int bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  err (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_net_set_nodelay (int) ; 
 int /*<<< orphan*/  usbip_net_set_reuseaddr (int) ; 
 int /*<<< orphan*/  usbip_net_set_v6only (int) ; 

__attribute__((used)) static int listen_all_addrinfo(struct addrinfo *ai_head, int sockfdlist[],
			     int maxsockfd)
{
	struct addrinfo *ai;
	int ret, nsockfd = 0;
	const size_t ai_buf_size = NI_MAXHOST + NI_MAXSERV + 2;
	char ai_buf[ai_buf_size];

	for (ai = ai_head; ai && nsockfd < maxsockfd; ai = ai->ai_next) {
		int sock;

		addrinfo_to_text(ai, ai_buf, ai_buf_size);
		dbg("opening %s", ai_buf);
		sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (sock < 0) {
			err("socket: %s: %d (%s)",
			    ai_buf, errno, strerror(errno));
			continue;
		}

		usbip_net_set_reuseaddr(sock);
		usbip_net_set_nodelay(sock);
		/* We use seperate sockets for IPv4 and IPv6
		 * (see do_standalone_mode()) */
		usbip_net_set_v6only(sock);

		ret = bind(sock, ai->ai_addr, ai->ai_addrlen);
		if (ret < 0) {
			err("bind: %s: %d (%s)",
			    ai_buf, errno, strerror(errno));
			close(sock);
			continue;
		}

		ret = listen(sock, SOMAXCONN);
		if (ret < 0) {
			err("listen: %s: %d (%s)",
			    ai_buf, errno, strerror(errno));
			close(sock);
			continue;
		}

		info("listening on %s", ai_buf);
		sockfdlist[nsockfd++] = sock;
	}

	return nsockfd;
}