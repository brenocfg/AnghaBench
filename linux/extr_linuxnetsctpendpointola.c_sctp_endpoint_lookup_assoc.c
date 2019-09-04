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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_transport {struct sctp_association* asoc; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ bind_addr; } ;
struct sctp_endpoint {TYPE_2__ base; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sctp_transport* sctp_epaddr_lookup_transport (struct sctp_endpoint const*,union sctp_addr const*) ; 

struct sctp_association *sctp_endpoint_lookup_assoc(
	const struct sctp_endpoint *ep,
	const union sctp_addr *paddr,
	struct sctp_transport **transport)
{
	struct sctp_association *asoc = NULL;
	struct sctp_transport *t;

	*transport = NULL;

	/* If the local port is not set, there can't be any associations
	 * on this endpoint.
	 */
	if (!ep->base.bind_addr.port)
		return NULL;

	rcu_read_lock();
	t = sctp_epaddr_lookup_transport(ep, paddr);
	if (!t)
		goto out;

	*transport = t;
	asoc = t->asoc;
out:
	rcu_read_unlock();
	return asoc;
}