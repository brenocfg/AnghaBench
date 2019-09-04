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
struct nfs4_stid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deleg_slab ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_stid*) ; 
 int /*<<< orphan*/  num_delegations ; 

__attribute__((used)) static void nfs4_free_deleg(struct nfs4_stid *stid)
{
	kmem_cache_free(deleg_slab, stid);
	atomic_long_dec(&num_delegations);
}