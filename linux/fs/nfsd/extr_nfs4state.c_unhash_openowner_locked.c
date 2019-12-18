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
struct TYPE_2__ {int /*<<< orphan*/  so_strhash; struct nfs4_client* so_client; } ;
struct nfs4_openowner {int /*<<< orphan*/  oo_perclient; TYPE_1__ oo_owner; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unhash_openowner_locked(struct nfs4_openowner *oo)
{
	struct nfs4_client *clp = oo->oo_owner.so_client;

	lockdep_assert_held(&clp->cl_lock);

	list_del_init(&oo->oo_owner.so_strhash);
	list_del_init(&oo->oo_perclient);
}