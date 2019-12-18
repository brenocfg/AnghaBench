#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nfs4_state_owner {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  seqid; } ;
struct TYPE_7__ {int /*<<< orphan*/  lr_ret; } ;
struct TYPE_6__ {int /*<<< orphan*/  res; int /*<<< orphan*/  arg; scalar_t__ roc; } ;
struct nfs4_closedata {TYPE_3__ arg; TYPE_5__* state; TYPE_2__ res; TYPE_1__ lr; } ;
struct TYPE_10__ {TYPE_4__* inode; struct nfs4_state_owner* owner; } ;
struct TYPE_9__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs4_closedata*) ; 
 int /*<<< orphan*/  nfs4_put_open_state (TYPE_5__*) ; 
 int /*<<< orphan*/  nfs4_put_state_owner (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  nfs_free_seqid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_sb_deactive (struct super_block*) ; 
 int /*<<< orphan*/  pnfs_roc_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_free_closedata(void *data)
{
	struct nfs4_closedata *calldata = data;
	struct nfs4_state_owner *sp = calldata->state->owner;
	struct super_block *sb = calldata->state->inode->i_sb;

	if (calldata->lr.roc)
		pnfs_roc_release(&calldata->lr.arg, &calldata->lr.res,
				calldata->res.lr_ret);
	nfs4_put_open_state(calldata->state);
	nfs_free_seqid(calldata->arg.seqid);
	nfs4_put_state_owner(sp);
	nfs_sb_deactive(sb);
	kfree(calldata);
}