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
struct nfsd4_blocked_lock {int /*<<< orphan*/  nbl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfsd4_blocked_lock*) ; 
 int /*<<< orphan*/  locks_delete_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_release_private (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_blocked_lock(struct nfsd4_blocked_lock *nbl)
{
	locks_delete_block(&nbl->nbl_lock);
	locks_release_private(&nbl->nbl_lock);
	kfree(nbl);
}