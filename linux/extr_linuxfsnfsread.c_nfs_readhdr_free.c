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
struct nfs_pgio_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  nfs_rdata_cachep ; 

__attribute__((used)) static void nfs_readhdr_free(struct nfs_pgio_header *rhdr)
{
	kmem_cache_free(nfs_rdata_cachep, rhdr);
}