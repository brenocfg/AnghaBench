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
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ *) ; 

void
pnfs_generic_pg_cleanup(struct nfs_pageio_descriptor *desc)
{
	if (desc->pg_lseg) {
		pnfs_put_lseg(desc->pg_lseg);
		desc->pg_lseg = NULL;
	}
}