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
struct rpc_task {int dummy; } ;
struct TYPE_4__ {TYPE_1__* context; } ;
struct nfs_pgio_header {int /*<<< orphan*/  pgio_mirror_idx; int /*<<< orphan*/  lseg; TYPE_2__ args; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EHOSTDOWN ; 
 int EIO ; 
 int /*<<< orphan*/  NFS_CONTEXT_BAD ; 
 scalar_t__ ff_layout_device_unavailable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_layout_read_record_layoutstats_start (struct rpc_task*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ff_layout_read_prepare_common(struct rpc_task *task,
					 struct nfs_pgio_header *hdr)
{
	if (unlikely(test_bit(NFS_CONTEXT_BAD, &hdr->args.context->flags))) {
		rpc_exit(task, -EIO);
		return -EIO;
	}
	if (ff_layout_device_unavailable(hdr->lseg, hdr->pgio_mirror_idx)) {
		rpc_exit(task, -EHOSTDOWN);
		return -EAGAIN;
	}

	ff_layout_read_record_layoutstats_start(task, hdr);
	return 0;
}