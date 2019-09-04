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
struct send_ctx {scalar_t__ cur_ino; int /*<<< orphan*/  deleted_refs; int /*<<< orphan*/  new_refs; TYPE_1__* cmp_key; } ;
struct TYPE_2__ {scalar_t__ objectid; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BTRFS_INODE_EXTREF_KEY ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int process_recorded_refs (struct send_ctx*,int*) ; 

__attribute__((used)) static int process_recorded_refs_if_needed(struct send_ctx *sctx, int at_end,
					   int *pending_move,
					   int *refs_processed)
{
	int ret = 0;

	if (sctx->cur_ino == 0)
		goto out;
	if (!at_end && sctx->cur_ino == sctx->cmp_key->objectid &&
	    sctx->cmp_key->type <= BTRFS_INODE_EXTREF_KEY)
		goto out;
	if (list_empty(&sctx->new_refs) && list_empty(&sctx->deleted_refs))
		goto out;

	ret = process_recorded_refs(sctx, pending_move);
	if (ret < 0)
		goto out;

	*refs_processed = 1;
out:
	return ret;
}