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
struct nfs_pageio_descriptor {int pg_mirror_count; int /*<<< orphan*/ * pg_mirrors_dynamic; int /*<<< orphan*/  pg_mirrors_static; int /*<<< orphan*/  pg_mirrors; scalar_t__ pg_mirror_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_pageio_cleanup_mirroring(struct nfs_pageio_descriptor *pgio)
{
	pgio->pg_mirror_count = 1;
	pgio->pg_mirror_idx = 0;
	pgio->pg_mirrors = pgio->pg_mirrors_static;
	kfree(pgio->pg_mirrors_dynamic);
	pgio->pg_mirrors_dynamic = NULL;
}