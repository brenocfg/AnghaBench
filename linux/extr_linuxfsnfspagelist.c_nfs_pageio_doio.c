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
struct nfs_pgio_mirror {scalar_t__ pg_base; scalar_t__ pg_count; int /*<<< orphan*/  pg_list; int /*<<< orphan*/  pg_bytes_written; } ;
struct nfs_pageio_descriptor {int pg_error; TYPE_1__* pg_ops; } ;
struct TYPE_2__ {int (* pg_doio ) (struct nfs_pageio_descriptor*) ;} ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 
 int stub1 (struct nfs_pageio_descriptor*) ; 

__attribute__((used)) static void nfs_pageio_doio(struct nfs_pageio_descriptor *desc)
{
	struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);


	if (!list_empty(&mirror->pg_list)) {
		int error = desc->pg_ops->pg_doio(desc);
		if (error < 0)
			desc->pg_error = error;
		else
			mirror->pg_bytes_written += mirror->pg_count;
	}
	if (list_empty(&mirror->pg_list)) {
		mirror->pg_count = 0;
		mirror->pg_base = 0;
	}
}