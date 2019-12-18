#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {scalar_t__ tk_status; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct nfs_pgio_header {TYPE_2__ args; TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_writeback_update_inode (struct nfs_pgio_header*) ; 

__attribute__((used)) static int nfs_write_done(struct rpc_task *task, struct nfs_pgio_header *hdr)
{
	if (task->tk_status >= 0) {
		hdr->res.count = hdr->args.count;
		nfs_writeback_update_inode(hdr);
	}
	return 0;
}