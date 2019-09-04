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

/* Variables and functions */
 int /*<<< orphan*/  inet6_register_protosw (int /*<<< orphan*/ *) ; 
 int proto_register (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctpv6_prot ; 
 int /*<<< orphan*/  sctpv6_seqpacket_protosw ; 
 int /*<<< orphan*/  sctpv6_stream_protosw ; 

int sctp_v6_protosw_init(void)
{
	int rc;

	rc = proto_register(&sctpv6_prot, 1);
	if (rc)
		return rc;

	/* Add SCTPv6(UDP and TCP style) to inetsw6 linked list. */
	inet6_register_protosw(&sctpv6_seqpacket_protosw);
	inet6_register_protosw(&sctpv6_stream_protosw);

	return 0;
}