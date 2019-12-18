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
typedef  scalar_t__ u32 ;
struct pnfs_layout_segment {int /*<<< orphan*/  pls_range; int /*<<< orphan*/  pls_seq; } ;
struct pnfs_layout_range {int dummy; } ;

/* Variables and functions */
 scalar_t__ pnfs_seqid_is_newer (int /*<<< orphan*/ ,scalar_t__) ; 
 int pnfs_should_free_range (int /*<<< orphan*/ *,struct pnfs_layout_range const*) ; 

__attribute__((used)) static bool
pnfs_match_lseg_recall(const struct pnfs_layout_segment *lseg,
		const struct pnfs_layout_range *recall_range,
		u32 seq)
{
	if (seq != 0 && pnfs_seqid_is_newer(lseg->pls_seq, seq))
		return false;
	if (recall_range == NULL)
		return true;
	return pnfs_should_free_range(&lseg->pls_range, recall_range);
}