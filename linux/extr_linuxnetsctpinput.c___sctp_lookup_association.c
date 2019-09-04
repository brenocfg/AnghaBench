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
struct sctp_transport {struct sctp_association* asoc; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sctp_transport* sctp_addrs_lookup_transport (struct net*,union sctp_addr const*,union sctp_addr const*) ; 

__attribute__((used)) static struct sctp_association *__sctp_lookup_association(
					struct net *net,
					const union sctp_addr *local,
					const union sctp_addr *peer,
					struct sctp_transport **pt)
{
	struct sctp_transport *t;
	struct sctp_association *asoc = NULL;

	t = sctp_addrs_lookup_transport(net, local, peer);
	if (!t)
		goto out;

	asoc = t->asoc;
	*pt = t;

out:
	return asoc;
}