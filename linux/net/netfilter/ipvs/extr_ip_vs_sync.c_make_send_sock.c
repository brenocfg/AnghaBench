#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ipvs_sockaddr {int dummy; } ipvs_sockaddr ;
struct socket {TYPE_1__* ops; int /*<<< orphan*/  sk; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {scalar_t__ mcast_af; int /*<<< orphan*/  mcast_ttl; } ;
struct netns_ipvs {TYPE_2__ mcfg; int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int (* connect ) (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_PMTUDISC_DONT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int bind_mcastif_addr (struct socket*,struct net_device*) ; 
 int /*<<< orphan*/  get_mcast_sockaddr (union ipvs_sockaddr*,int*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int set_mcast_if (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  set_mcast_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mcast_pmtudisc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mcast_ttl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sock_size (int /*<<< orphan*/ ,int,int) ; 
 int sock_create_kern (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int stub1 (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int sysctl_sync_sock_size (struct netns_ipvs*) ; 

__attribute__((used)) static int make_send_sock(struct netns_ipvs *ipvs, int id,
			  struct net_device *dev, struct socket **sock_ret)
{
	/* multicast addr */
	union ipvs_sockaddr mcast_addr;
	struct socket *sock;
	int result, salen;

	/* First create a socket */
	result = sock_create_kern(ipvs->net, ipvs->mcfg.mcast_af, SOCK_DGRAM,
				  IPPROTO_UDP, &sock);
	if (result < 0) {
		pr_err("Error during creation of socket; terminating\n");
		goto error;
	}
	*sock_ret = sock;
	result = set_mcast_if(sock->sk, dev);
	if (result < 0) {
		pr_err("Error setting outbound mcast interface\n");
		goto error;
	}

	set_mcast_loop(sock->sk, 0);
	set_mcast_ttl(sock->sk, ipvs->mcfg.mcast_ttl);
	/* Allow fragmentation if MTU changes */
	set_mcast_pmtudisc(sock->sk, IP_PMTUDISC_DONT);
	result = sysctl_sync_sock_size(ipvs);
	if (result > 0)
		set_sock_size(sock->sk, 1, result);

	if (AF_INET == ipvs->mcfg.mcast_af)
		result = bind_mcastif_addr(sock, dev);
	else
		result = 0;
	if (result < 0) {
		pr_err("Error binding address of the mcast interface\n");
		goto error;
	}

	get_mcast_sockaddr(&mcast_addr, &salen, &ipvs->mcfg, id);
	result = sock->ops->connect(sock, (struct sockaddr *) &mcast_addr,
				    salen, 0);
	if (result < 0) {
		pr_err("Error connecting to the multicast addr\n");
		goto error;
	}

	return 0;

error:
	return result;
}