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
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_transport_destroy (struct sctp_transport*) ; 

void sctp_transport_put(struct sctp_transport *transport)
{
	if (refcount_dec_and_test(&transport->refcnt))
		sctp_transport_destroy(transport);
}