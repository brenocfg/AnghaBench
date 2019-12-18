#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  udp_addr ;
struct udp_port_cfg {int /*<<< orphan*/  use_udp_checksums; scalar_t__ peer_udp_port; int /*<<< orphan*/  peer_ip; scalar_t__ local_udp_port; int /*<<< orphan*/  local_ip; scalar_t__ bind_ifindex; } ;
struct socket {TYPE_1__* sk; } ;
struct sockaddr_in {scalar_t__ sin_port; int /*<<< orphan*/  sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int sk_no_check_tx; } ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BINDTOIFINDEX ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int kernel_connect (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int sock_create_kern (struct net*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

int udp_sock_create4(struct net *net, struct udp_port_cfg *cfg,
		     struct socket **sockp)
{
	int err;
	struct socket *sock = NULL;
	struct sockaddr_in udp_addr;

	err = sock_create_kern(net, AF_INET, SOCK_DGRAM, 0, &sock);
	if (err < 0)
		goto error;

	if (cfg->bind_ifindex) {
		err = kernel_setsockopt(sock, SOL_SOCKET, SO_BINDTOIFINDEX,
					(void *)&cfg->bind_ifindex,
					sizeof(cfg->bind_ifindex));
		if (err < 0)
			goto error;
	}

	udp_addr.sin_family = AF_INET;
	udp_addr.sin_addr = cfg->local_ip;
	udp_addr.sin_port = cfg->local_udp_port;
	err = kernel_bind(sock, (struct sockaddr *)&udp_addr,
			  sizeof(udp_addr));
	if (err < 0)
		goto error;

	if (cfg->peer_udp_port) {
		udp_addr.sin_family = AF_INET;
		udp_addr.sin_addr = cfg->peer_ip;
		udp_addr.sin_port = cfg->peer_udp_port;
		err = kernel_connect(sock, (struct sockaddr *)&udp_addr,
				     sizeof(udp_addr), 0);
		if (err < 0)
			goto error;
	}

	sock->sk->sk_no_check_tx = !cfg->use_udp_checksums;

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