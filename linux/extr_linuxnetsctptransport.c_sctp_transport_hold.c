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
struct sctp_transport {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

int sctp_transport_hold(struct sctp_transport *transport)
{
	return refcount_inc_not_zero(&transport->refcnt);
}