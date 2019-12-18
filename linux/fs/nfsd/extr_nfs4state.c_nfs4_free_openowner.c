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
struct nfs4_stateowner {int dummy; } ;
struct nfs4_openowner {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_openowner*) ; 
 struct nfs4_openowner* openowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  openowner_slab ; 

__attribute__((used)) static void nfs4_free_openowner(struct nfs4_stateowner *so)
{
	struct nfs4_openowner *oo = openowner(so);

	kmem_cache_free(openowner_slab, oo);
}