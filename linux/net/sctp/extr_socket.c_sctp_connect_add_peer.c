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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_transport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct sctp_endpoint {TYPE_1__ base; } ;
struct sctp_association {scalar_t__ state; struct sctp_endpoint* ep; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EALREADY ; 
 int EISCONN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SCTP_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  SCTP_UNKNOWN ; 
 struct sctp_transport* sctp_assoc_add_peer (struct sctp_association*,union sctp_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_endpoint_is_peeled_off (struct sctp_endpoint*,union sctp_addr*) ; 
 struct sctp_association* sctp_endpoint_lookup_assoc (struct sctp_endpoint*,union sctp_addr*,struct sctp_transport**) ; 
 int sctp_verify_addr (int /*<<< orphan*/ ,union sctp_addr*,int) ; 

__attribute__((used)) static int sctp_connect_add_peer(struct sctp_association *asoc,
				 union sctp_addr *daddr, int addr_len)
{
	struct sctp_endpoint *ep = asoc->ep;
	struct sctp_association *old;
	struct sctp_transport *t;
	int err;

	err = sctp_verify_addr(ep->base.sk, daddr, addr_len);
	if (err)
		return err;

	old = sctp_endpoint_lookup_assoc(ep, daddr, &t);
	if (old && old != asoc)
		return old->state >= SCTP_STATE_ESTABLISHED ? -EISCONN
							    : -EALREADY;

	if (sctp_endpoint_is_peeled_off(ep, daddr))
		return -EADDRNOTAVAIL;

	t = sctp_assoc_add_peer(asoc, daddr, GFP_KERNEL, SCTP_UNKNOWN);
	if (!t)
		return -ENOMEM;

	return 0;
}