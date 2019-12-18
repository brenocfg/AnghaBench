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
struct sctp_transport {int /*<<< orphan*/  rcu; scalar_t__ asoc; int /*<<< orphan*/  packet; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,struct sctp_transport*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_association_put (scalar_t__) ; 
 int /*<<< orphan*/  sctp_packet_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_transport_destroy_rcu ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_transport_destroy(struct sctp_transport *transport)
{
	if (unlikely(refcount_read(&transport->refcnt))) {
		WARN(1, "Attempt to destroy undead transport %p!\n", transport);
		return;
	}

	sctp_packet_free(&transport->packet);

	if (transport->asoc)
		sctp_association_put(transport->asoc);

	call_rcu(&transport->rcu, sctp_transport_destroy_rcu);
}