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
 int /*<<< orphan*/  inet6_unregister_protosw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctpv6_prot ; 
 int /*<<< orphan*/  sctpv6_seqpacket_protosw ; 
 int /*<<< orphan*/  sctpv6_stream_protosw ; 

void sctp_v6_protosw_exit(void)
{
	inet6_unregister_protosw(&sctpv6_seqpacket_protosw);
	inet6_unregister_protosw(&sctpv6_stream_protosw);
	proto_unregister(&sctpv6_prot);
}