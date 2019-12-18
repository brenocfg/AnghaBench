#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct socket {TYPE_3__* ops; TYPE_2__* sk; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int ss_family; } ;
struct TCP_Server_Info {struct socket* ssocket; scalar_t__ noblockcnt; scalar_t__ tcp_nodelay; scalar_t__ noautotune; TYPE_1__ dstaddr; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_6__ {int (* connect ) (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int sk_rcvtimeo; int sk_sndtimeo; int sk_sndbuf; int sk_rcvbuf; int /*<<< orphan*/  sk_allocation; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int HZ ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  RFC1001_PORT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  VFS ; 
 int __sock_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**,int) ; 
 int bind_socket (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_net_ns (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_reclassify_socket4 (struct socket*) ; 
 int /*<<< orphan*/  cifs_reclassify_socket6 (struct socket*) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ip_rfc1001_connect (struct TCP_Server_Info*) ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int stub1 (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
generic_ip_connect(struct TCP_Server_Info *server)
{
	int rc = 0;
	__be16 sport;
	int slen, sfamily;
	struct socket *socket = server->ssocket;
	struct sockaddr *saddr;

	saddr = (struct sockaddr *) &server->dstaddr;

	if (server->dstaddr.ss_family == AF_INET6) {
		sport = ((struct sockaddr_in6 *) saddr)->sin6_port;
		slen = sizeof(struct sockaddr_in6);
		sfamily = AF_INET6;
	} else {
		sport = ((struct sockaddr_in *) saddr)->sin_port;
		slen = sizeof(struct sockaddr_in);
		sfamily = AF_INET;
	}

	if (socket == NULL) {
		rc = __sock_create(cifs_net_ns(server), sfamily, SOCK_STREAM,
				   IPPROTO_TCP, &socket, 1);
		if (rc < 0) {
			cifs_server_dbg(VFS, "Error %d creating socket\n", rc);
			server->ssocket = NULL;
			return rc;
		}

		/* BB other socket options to set KEEPALIVE, NODELAY? */
		cifs_dbg(FYI, "Socket created\n");
		server->ssocket = socket;
		socket->sk->sk_allocation = GFP_NOFS;
		if (sfamily == AF_INET6)
			cifs_reclassify_socket6(socket);
		else
			cifs_reclassify_socket4(socket);
	}

	rc = bind_socket(server);
	if (rc < 0)
		return rc;

	/*
	 * Eventually check for other socket options to change from
	 * the default. sock_setsockopt not used because it expects
	 * user space buffer
	 */
	socket->sk->sk_rcvtimeo = 7 * HZ;
	socket->sk->sk_sndtimeo = 5 * HZ;

	/* make the bufsizes depend on wsize/rsize and max requests */
	if (server->noautotune) {
		if (socket->sk->sk_sndbuf < (200 * 1024))
			socket->sk->sk_sndbuf = 200 * 1024;
		if (socket->sk->sk_rcvbuf < (140 * 1024))
			socket->sk->sk_rcvbuf = 140 * 1024;
	}

	if (server->tcp_nodelay) {
		int val = 1;
		rc = kernel_setsockopt(socket, SOL_TCP, TCP_NODELAY,
				(char *)&val, sizeof(val));
		if (rc)
			cifs_dbg(FYI, "set TCP_NODELAY socket option error %d\n",
				 rc);
	}

	cifs_dbg(FYI, "sndbuf %d rcvbuf %d rcvtimeo 0x%lx\n",
		 socket->sk->sk_sndbuf,
		 socket->sk->sk_rcvbuf, socket->sk->sk_rcvtimeo);

	rc = socket->ops->connect(socket, saddr, slen,
				  server->noblockcnt ? O_NONBLOCK : 0);
	/*
	 * When mounting SMB root file systems, we do not want to block in
	 * connect. Otherwise bail out and then let cifs_reconnect() perform
	 * reconnect failover - if possible.
	 */
	if (server->noblockcnt && rc == -EINPROGRESS)
		rc = 0;
	if (rc < 0) {
		cifs_dbg(FYI, "Error %d connecting to server\n", rc);
		sock_release(socket);
		server->ssocket = NULL;
		return rc;
	}

	if (sport == htons(RFC1001_PORT))
		rc = ip_rfc1001_connect(server);

	return rc;
}