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
struct sctp_transport {struct sctp_association* asoc; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_association_hold (struct sctp_association*) ; 

void sctp_transport_set_owner(struct sctp_transport *transport,
			      struct sctp_association *asoc)
{
	transport->asoc = asoc;
	sctp_association_hold(asoc);
}