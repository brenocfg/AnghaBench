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
 int /*<<< orphan*/  inet_register_protosw (int /*<<< orphan*/ *) ; 
 int proto_register (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_prot ; 
 int /*<<< orphan*/  sctp_seqpacket_protosw ; 
 int /*<<< orphan*/  sctp_stream_protosw ; 

__attribute__((used)) static int sctp_v4_protosw_init(void)
{
	int rc;

	rc = proto_register(&sctp_prot, 1);
	if (rc)
		return rc;

	/* Register SCTP(UDP and TCP style) with socket layer.  */
	inet_register_protosw(&sctp_seqpacket_protosw);
	inet_register_protosw(&sctp_stream_protosw);

	return 0;
}