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
struct sctp_association {scalar_t__ addip_last_asconf; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_assoc_free_asconf_acks (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_assoc_free_asconf_queue (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_chunk_free (scalar_t__) ; 

void sctp_asconf_queue_teardown(struct sctp_association *asoc)
{
	/* Free any cached ASCONF_ACK chunk. */
	sctp_assoc_free_asconf_acks(asoc);

	/* Free the ASCONF queue. */
	sctp_assoc_free_asconf_queue(asoc);

	/* Free any cached ASCONF chunk. */
	if (asoc->addip_last_asconf)
		sctp_chunk_free(asoc->addip_last_asconf);
}