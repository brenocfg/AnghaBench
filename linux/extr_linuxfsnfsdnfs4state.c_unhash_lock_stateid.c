#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sc_client; } ;
struct nfs4_ol_stateid {TYPE_2__ st_stid; int /*<<< orphan*/  st_locks; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_unhash_stid (TYPE_2__*) ; 
 int unhash_ol_stateid (struct nfs4_ol_stateid*) ; 

__attribute__((used)) static bool unhash_lock_stateid(struct nfs4_ol_stateid *stp)
{
	lockdep_assert_held(&stp->st_stid.sc_client->cl_lock);

	list_del_init(&stp->st_locks);
	nfs4_unhash_stid(&stp->st_stid);
	return unhash_ol_stateid(stp);
}