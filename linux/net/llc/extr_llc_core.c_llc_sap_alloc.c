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
struct llc_sap {int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * sk_laddr_hash; int /*<<< orphan*/  sk_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NULLS_HEAD (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LLC_SAP_STATE_ACTIVE ; 
 int LLC_SK_LADDR_HASH_ENTRIES ; 
 struct llc_sap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct llc_sap *llc_sap_alloc(void)
{
	struct llc_sap *sap = kzalloc(sizeof(*sap), GFP_ATOMIC);
	int i;

	if (sap) {
		/* sap->laddr.mac - leave as a null, it's filled by bind */
		sap->state = LLC_SAP_STATE_ACTIVE;
		spin_lock_init(&sap->sk_lock);
		for (i = 0; i < LLC_SK_LADDR_HASH_ENTRIES; i++)
			INIT_HLIST_NULLS_HEAD(&sap->sk_laddr_hash[i], i);
		refcount_set(&sap->refcnt, 1);
	}
	return sap;
}