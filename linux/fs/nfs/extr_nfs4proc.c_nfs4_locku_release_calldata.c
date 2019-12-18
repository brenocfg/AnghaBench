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
struct TYPE_2__ {int /*<<< orphan*/  seqid; } ;
struct nfs4_unlockdata {int /*<<< orphan*/  ctx; int /*<<< orphan*/  l_ctx; int /*<<< orphan*/  lsp; TYPE_1__ arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs4_unlockdata*) ; 
 int /*<<< orphan*/  nfs4_put_lock_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_free_seqid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_put_lock_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_nfs_open_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_locku_release_calldata(void *data)
{
	struct nfs4_unlockdata *calldata = data;
	nfs_free_seqid(calldata->arg.seqid);
	nfs4_put_lock_state(calldata->lsp);
	nfs_put_lock_context(calldata->l_ctx);
	put_nfs_open_context(calldata->ctx);
	kfree(calldata);
}