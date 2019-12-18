#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; } ;
struct TYPE_7__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_5__ v6; TYPE_1__ sa; } ;
struct TYPE_8__ {scalar_t__ freebind; int /*<<< orphan*/  sk; } ;
struct sctp_sock {TYPE_6__* pf; TYPE_2__ inet; } ;
struct sctp_af {int (* available ) (union sctp_addr*,struct sctp_sock*) ;} ;
struct net_device {int dummy; } ;
struct TYPE_9__ {scalar_t__ ip_nonlocal_bind; } ;
struct TYPE_10__ {TYPE_3__ sysctl; } ;
struct net {TYPE_4__ ipv6; } ;
struct TYPE_12__ {struct sctp_af* af; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int IPV6_ADDR_LINKLOCAL ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_chk_addr (struct net*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sctp_af* sctp_get_af_specific (scalar_t__) ; 
 struct net* sock_net (int /*<<< orphan*/ *) ; 
 int stub1 (union sctp_addr*,struct sctp_sock*) ; 

__attribute__((used)) static int sctp_inet6_bind_verify(struct sctp_sock *opt, union sctp_addr *addr)
{
	struct sctp_af *af;

	/* ASSERT: address family has already been verified. */
	if (addr->sa.sa_family != AF_INET6)
		af = sctp_get_af_specific(addr->sa.sa_family);
	else {
		int type = ipv6_addr_type(&addr->v6.sin6_addr);
		struct net_device *dev;

		if (type & IPV6_ADDR_LINKLOCAL) {
			struct net *net;
			if (!addr->v6.sin6_scope_id)
				return 0;
			net = sock_net(&opt->inet.sk);
			rcu_read_lock();
			dev = dev_get_by_index_rcu(net, addr->v6.sin6_scope_id);
			if (!dev || !(opt->inet.freebind ||
				      net->ipv6.sysctl.ip_nonlocal_bind ||
				      ipv6_chk_addr(net, &addr->v6.sin6_addr,
						    dev, 0))) {
				rcu_read_unlock();
				return 0;
			}
			rcu_read_unlock();
		}

		af = opt->pf->af;
	}
	return af->available(addr, opt);
}