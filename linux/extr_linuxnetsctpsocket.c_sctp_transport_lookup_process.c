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
typedef  union sctp_addr {int dummy; } sctp_addr ;
typedef  struct sctp_transport sctp_transport ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sctp_transport* sctp_addrs_lookup_transport (struct net*,union sctp_addr const*,union sctp_addr const*) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 

int sctp_transport_lookup_process(int (*cb)(struct sctp_transport *, void *),
				  struct net *net,
				  const union sctp_addr *laddr,
				  const union sctp_addr *paddr, void *p)
{
	struct sctp_transport *transport;
	int err;

	rcu_read_lock();
	transport = sctp_addrs_lookup_transport(net, laddr, paddr);
	rcu_read_unlock();
	if (!transport)
		return -ENOENT;

	err = cb(transport, p);
	sctp_transport_put(transport);

	return err;
}