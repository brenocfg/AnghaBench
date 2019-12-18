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
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct TYPE_4__ {int /*<<< orphan*/ * s6_addr32; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct smc_clc_msg_proposal_prefix {int dummy; } ;
struct smc_clc_ipv6_prefix {int dummy; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOTCONN ; 
 scalar_t__ PF_INET ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 scalar_t__ ipv6_addr_v4mapped (TYPE_2__*) ; 
 int /*<<< orphan*/  kernel_getsockname (struct socket*,struct sockaddr*) ; 
 int /*<<< orphan*/  memset (struct smc_clc_msg_proposal_prefix*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dst_entry* sk_dst_get (int /*<<< orphan*/ ) ; 
 int smc_clc_prfx_set4_rcu (struct dst_entry*,int /*<<< orphan*/ ,struct smc_clc_msg_proposal_prefix*) ; 
 int smc_clc_prfx_set6_rcu (struct dst_entry*,struct smc_clc_msg_proposal_prefix*,struct smc_clc_ipv6_prefix*) ; 

__attribute__((used)) static int smc_clc_prfx_set(struct socket *clcsock,
			    struct smc_clc_msg_proposal_prefix *prop,
			    struct smc_clc_ipv6_prefix *ipv6_prfx)
{
	struct dst_entry *dst = sk_dst_get(clcsock->sk);
	struct sockaddr_storage addrs;
	struct sockaddr_in6 *addr6;
	struct sockaddr_in *addr;
	int rc = -ENOENT;

	memset(prop, 0, sizeof(*prop));
	if (!dst) {
		rc = -ENOTCONN;
		goto out;
	}
	if (!dst->dev) {
		rc = -ENODEV;
		goto out_rel;
	}
	/* get address to which the internal TCP socket is bound */
	kernel_getsockname(clcsock, (struct sockaddr *)&addrs);
	/* analyze IP specific data of net_device belonging to TCP socket */
	addr6 = (struct sockaddr_in6 *)&addrs;
	rcu_read_lock();
	if (addrs.ss_family == PF_INET) {
		/* IPv4 */
		addr = (struct sockaddr_in *)&addrs;
		rc = smc_clc_prfx_set4_rcu(dst, addr->sin_addr.s_addr, prop);
	} else if (ipv6_addr_v4mapped(&addr6->sin6_addr)) {
		/* mapped IPv4 address - peer is IPv4 only */
		rc = smc_clc_prfx_set4_rcu(dst, addr6->sin6_addr.s6_addr32[3],
					   prop);
	} else {
		/* IPv6 */
		rc = smc_clc_prfx_set6_rcu(dst, prop, ipv6_prfx);
	}
	rcu_read_unlock();
out_rel:
	dst_release(dst);
out:
	return rc;
}