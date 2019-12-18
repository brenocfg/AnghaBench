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
struct pnfs_layout_segment {int /*<<< orphan*/  pls_layout; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_lseg_invalid (struct pnfs_layout_segment*,struct list_head*) ; 
 int /*<<< orphan*/  pnfs_cache_lseg_for_layoutreturn (int /*<<< orphan*/ ,struct pnfs_layout_segment*) ; 

__attribute__((used)) static int
mark_lseg_invalid_or_return(struct pnfs_layout_segment *lseg,
		struct list_head *tmp_list)
{
	if (!mark_lseg_invalid(lseg, tmp_list))
		return 0;
	pnfs_cache_lseg_for_layoutreturn(lseg->pls_layout, lseg);
	return 1;
}