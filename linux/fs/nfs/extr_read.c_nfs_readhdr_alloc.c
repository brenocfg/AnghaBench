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
struct nfs_pgio_header {int /*<<< orphan*/  rw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs_pgio_header* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_rdata_cachep ; 

__attribute__((used)) static struct nfs_pgio_header *nfs_readhdr_alloc(void)
{
	struct nfs_pgio_header *p = kmem_cache_zalloc(nfs_rdata_cachep, GFP_KERNEL);

	if (p)
		p->rw_mode = FMODE_READ;
	return p;
}