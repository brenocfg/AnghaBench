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
struct nfs4_ol_stateid {TYPE_2__ st_stid; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ol_stateid_reaplist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ol_stateid_locked (struct nfs4_ol_stateid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reaplist ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unhash_open_stateid (struct nfs4_ol_stateid*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_open_stateid(struct nfs4_ol_stateid *stp)
{
	LIST_HEAD(reaplist);

	spin_lock(&stp->st_stid.sc_client->cl_lock);
	if (unhash_open_stateid(stp, &reaplist))
		put_ol_stateid_locked(stp, &reaplist);
	spin_unlock(&stp->st_stid.sc_client->cl_lock);
	free_ol_stateid_reaplist(&reaplist);
}