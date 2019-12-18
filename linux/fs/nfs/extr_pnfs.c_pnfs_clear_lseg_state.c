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
struct pnfs_layout_segment {int /*<<< orphan*/  pls_flags; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LSEG_LAYOUTCOMMIT ; 
 int /*<<< orphan*/  NFS_LSEG_LAYOUTRETURN ; 
 int /*<<< orphan*/  NFS_LSEG_ROC ; 
 int /*<<< orphan*/  NFS_LSEG_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_lseg_dec_and_remove_zero (struct pnfs_layout_segment*,struct list_head*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_clear_lseg_state(struct pnfs_layout_segment *lseg,
		struct list_head *free_me)
{
	clear_bit(NFS_LSEG_ROC, &lseg->pls_flags);
	clear_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags);
	if (test_and_clear_bit(NFS_LSEG_VALID, &lseg->pls_flags))
		pnfs_lseg_dec_and_remove_zero(lseg, free_me);
	if (test_and_clear_bit(NFS_LSEG_LAYOUTCOMMIT, &lseg->pls_flags))
		pnfs_lseg_dec_and_remove_zero(lseg, free_me);
}