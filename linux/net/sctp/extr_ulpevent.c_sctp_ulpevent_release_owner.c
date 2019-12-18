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
struct sctp_ulpevent {int /*<<< orphan*/  rmem_len; struct sctp_association* asoc; } ;
struct sctp_association {int /*<<< orphan*/  rmem_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_association_put (struct sctp_association*) ; 

__attribute__((used)) static inline void sctp_ulpevent_release_owner(struct sctp_ulpevent *event)
{
	struct sctp_association *asoc = event->asoc;

	atomic_sub(event->rmem_len, &asoc->rmem_alloc);
	sctp_association_put(asoc);
}