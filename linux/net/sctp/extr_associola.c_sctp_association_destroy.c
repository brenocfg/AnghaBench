#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sk; int /*<<< orphan*/  dead; } ;
struct sctp_association {scalar_t__ assoc_id; int /*<<< orphan*/  rmem_alloc; TYPE_1__ base; int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,struct sctp_association*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assoc ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree_rcu (struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  sctp_assocs_id ; 
 int /*<<< orphan*/  sctp_assocs_id_lock ; 
 int /*<<< orphan*/  sctp_endpoint_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sctp_association_destroy(struct sctp_association *asoc)
{
	if (unlikely(!asoc->base.dead)) {
		WARN(1, "Attempt to destroy undead association %p!\n", asoc);
		return;
	}

	sctp_endpoint_put(asoc->ep);
	sock_put(asoc->base.sk);

	if (asoc->assoc_id != 0) {
		spin_lock_bh(&sctp_assocs_id_lock);
		idr_remove(&sctp_assocs_id, asoc->assoc_id);
		spin_unlock_bh(&sctp_assocs_id_lock);
	}

	WARN_ON(atomic_read(&asoc->rmem_alloc));

	kfree_rcu(asoc, rcu);
	SCTP_DBG_OBJCNT_DEC(assoc);
}