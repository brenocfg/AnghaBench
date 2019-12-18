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
struct sctp_transport {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ sctp_lookup_association (struct net*,union sctp_addr const*,union sctp_addr const*,struct sctp_transport**) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 

bool sctp_has_association(struct net *net,
			  const union sctp_addr *laddr,
			  const union sctp_addr *paddr)
{
	struct sctp_transport *transport;

	if (sctp_lookup_association(net, laddr, paddr, &transport)) {
		sctp_transport_put(transport);
		return true;
	}

	return false;
}