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
struct pnfs_layout_segment {int dummy; } ;
struct pnfs_layout_hdr {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_lseg_merge ; 
 int /*<<< orphan*/  ff_lseg_range_is_after ; 
 int /*<<< orphan*/  pnfs_generic_layout_insert_lseg (struct pnfs_layout_hdr*,struct pnfs_layout_segment*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct list_head*) ; 

__attribute__((used)) static void
ff_layout_add_lseg(struct pnfs_layout_hdr *lo,
		struct pnfs_layout_segment *lseg,
		struct list_head *free_me)
{
	pnfs_generic_layout_insert_lseg(lo, lseg,
			ff_lseg_range_is_after,
			ff_lseg_merge,
			free_me);
}