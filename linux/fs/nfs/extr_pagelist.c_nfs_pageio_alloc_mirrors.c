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
struct nfs_pgio_mirror {int dummy; } ;
struct nfs_pageio_descriptor {struct nfs_pgio_mirror* pg_mirrors_dynamic; int /*<<< orphan*/  pg_bsize; struct nfs_pgio_mirror* pg_mirrors_static; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct nfs_pgio_mirror*) ; 
 struct nfs_pgio_mirror* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_mirror_init (struct nfs_pgio_mirror*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs_pgio_mirror *
nfs_pageio_alloc_mirrors(struct nfs_pageio_descriptor *desc,
		unsigned int mirror_count)
{
	struct nfs_pgio_mirror *ret;
	unsigned int i;

	kfree(desc->pg_mirrors_dynamic);
	desc->pg_mirrors_dynamic = NULL;
	if (mirror_count == 1)
		return desc->pg_mirrors_static;
	ret = kmalloc_array(mirror_count, sizeof(*ret), GFP_KERNEL);
	if (ret != NULL) {
		for (i = 0; i < mirror_count; i++)
			nfs_pageio_mirror_init(&ret[i], desc->pg_bsize);
		desc->pg_mirrors_dynamic = ret;
	}
	return ret;
}