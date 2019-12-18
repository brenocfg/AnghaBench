#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nfs_pageio_descriptor {scalar_t__ pg_mirror_count; scalar_t__ pg_error; TYPE_1__* pg_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pg_cleanup ) (struct nfs_pageio_descriptor*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_pageio_cleanup_mirroring (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_complete_mirror (struct nfs_pageio_descriptor*,scalar_t__) ; 
 int /*<<< orphan*/  nfs_pageio_error_cleanup (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pageio_descriptor*) ; 

void nfs_pageio_complete(struct nfs_pageio_descriptor *desc)
{
	u32 midx;

	for (midx = 0; midx < desc->pg_mirror_count; midx++)
		nfs_pageio_complete_mirror(desc, midx);

	if (desc->pg_error < 0)
		nfs_pageio_error_cleanup(desc);
	if (desc->pg_ops->pg_cleanup)
		desc->pg_ops->pg_cleanup(desc);
	nfs_pageio_cleanup_mirroring(desc);
}