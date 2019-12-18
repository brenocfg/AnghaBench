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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  udp6_addr ;
struct udp_port_cfg {int /*<<< orphan*/  use_udp6_rx_checksums; int /*<<< orphan*/  use_udp6_tx_checksums; scalar_t__ peer_udp_port; int /*<<< orphan*/  peer_ip6; scalar_t__ local_udp_port; int /*<<< orphan*/  local_ip6; scalar_t__ bind_ifindex; scalar_t__ ipv6_v6only; } ;
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; void* sin6_family; } ;
struct sockaddr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 void* AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BINDTOIFINDEX ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int kernel_connect (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int sock_create_kern (struct net*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  udp_set_no_check6_rx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udp_set_no_check6_tx (int /*<<< orphan*/ ,int) ; 

int udp_sock_create6(struct net *net, struct udp_port_cfg *cfg,
		     struct socket **sockp)
{
	struct sockaddr_in6 udp6_addr = {};
	int err;
	struct socket *sock = NULL;

	err = sock_create_kern(net, AF_INET6, SOCK_DGRAM, 0, &sock);
	if (err < 0)
		goto error;

	if (cfg->ipv6_v6only) {
		int val = 1;

		err = kernel_setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
					(char *) &val, sizeof(val));
		if (err < 0)
			goto error;
	}
	if (cfg->bind_ifindex) {
		err = kernel_setsockopt(sock, SOL_SOCKET, SO_BINDTOIFINDEX,
					(void *)&cfg->bind_ifindex,
					sizeof(cfg->bind_ifindex));
		if (err < 0)
			goto error;
	}

	udp6_addr.sin6_family = AF_INET6;
	memcpy(&udp6_addr.sin6_addr, &cfg->local_ip6,
	       sizeof(udp6_addr.sin6_addr));
	udp6_addr.sin6_port = cfg->local_udp_port;
	err = kernel_bind(sock, (struct sockaddr *)&udp6_addr,
			  sizeof(udp6_addr));
	if (err < 0)
		goto error;

	if (cfg->peer_udp_port) {
		memset(&udp6_addr, 0, sizeof(udp6_addr));
		udp6_addr.sin6_family = AF_INET6;
		memcpy(&udp6_addr.sin6_addr, &cfg->peer_ip6,
		       sizeof(udp6_addr.sin6_addr));
		udp6_addr.sin6_port = cfg->peer_udp_port;
		err = kernel_connect(sock,
				     (struct sockaddr *)&udp6_addr,
				     sizeof(udp6_addr), 0);
	}
	if (err < 0)
		goto error;

	udp_set_no_check6_tx(sock->sk, !cfg->use_udp6_tx_checksums);
	udp_set_no_check6_rx(sock->sk, !cfg->use_udp6_rx_checksums);

	*sockp = sock;
	return 0;

error:
	if (sock) {
		kernel_sock_shutdown(sock, SHUT_RDWR);
		sock_release(sock);
	}
	*sockp = NULL;
	return err;
}