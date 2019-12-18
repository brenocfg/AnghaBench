#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct TYPE_7__ {TYPE_2__* verf; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct nfs_pgio_header {TYPE_4__* lseg; TYPE_3__ res; TYPE_1__ args; int /*<<< orphan*/  pgio_mirror_idx; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  pls_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  committed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_LAYOUT_COMP (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_IOHDR_STAT ; 
 int /*<<< orphan*/  NFS_LSEG_LAYOUTRETURN ; 
 int /*<<< orphan*/  nfs4_ff_layout_stat_io_end_write (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ff_layout_write_record_layoutstats_done(struct rpc_task *task,
		struct nfs_pgio_header *hdr)
{
	if (!test_and_clear_bit(NFS_IOHDR_STAT, &hdr->flags))
		return;
	nfs4_ff_layout_stat_io_end_write(task,
			FF_LAYOUT_COMP(hdr->lseg, hdr->pgio_mirror_idx),
			hdr->args.count, hdr->res.count,
			hdr->res.verf->committed);
	set_bit(NFS_LSEG_LAYOUTRETURN, &hdr->lseg->pls_flags);
}