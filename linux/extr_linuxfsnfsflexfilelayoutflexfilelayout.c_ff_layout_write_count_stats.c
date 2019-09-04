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
struct rpc_task {int dummy; } ;
struct nfs_pgio_header {int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cl_metrics; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_WRITE ; 
 TYPE_1__* NFS_CLIENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_layout_write_record_layoutstats_done (struct rpc_task*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  rpc_count_iostats_metrics (struct rpc_task*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ff_layout_write_count_stats(struct rpc_task *task, void *data)
{
	struct nfs_pgio_header *hdr = data;

	ff_layout_write_record_layoutstats_done(task, hdr);
	rpc_count_iostats_metrics(task,
	    &NFS_CLIENT(hdr->inode)->cl_metrics[NFSPROC4_CLNT_WRITE]);
}