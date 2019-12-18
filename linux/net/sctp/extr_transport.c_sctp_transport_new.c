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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (struct sctp_transport*) ; 
 int /*<<< orphan*/  kfree (struct sctp_transport*) ; 
 struct sctp_transport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_transport_init (struct net*,struct sctp_transport*,union sctp_addr const*,int /*<<< orphan*/ ) ; 

struct sctp_transport *sctp_transport_new(struct net *net,
					  const union sctp_addr *addr,
					  gfp_t gfp)
{
	struct sctp_transport *transport;

	transport = kzalloc(sizeof(*transport), gfp);
	if (!transport)
		goto fail;

	if (!sctp_transport_init(net, transport, addr, gfp))
		goto fail_init;

	SCTP_DBG_OBJCNT_INC(transport);

	return transport;

fail_init:
	kfree(transport);

fail:
	return NULL;
}