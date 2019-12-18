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
struct pnfs_layout_segment {int /*<<< orphan*/  pls_list; int /*<<< orphan*/  pls_layout; int /*<<< orphan*/  pls_refcount; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pnfs_layout_remove_lseg (int /*<<< orphan*/ ,struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool pnfs_lseg_dec_and_remove_zero(struct pnfs_layout_segment *lseg,
		struct list_head *tmp_list)
{
	if (!refcount_dec_and_test(&lseg->pls_refcount))
		return false;
	pnfs_layout_remove_lseg(lseg->pls_layout, lseg);
	list_add(&lseg->pls_list, tmp_list);
	return true;
}