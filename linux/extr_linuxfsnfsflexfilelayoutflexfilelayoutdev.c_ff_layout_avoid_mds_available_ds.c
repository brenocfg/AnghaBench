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

/* Variables and functions */
 scalar_t__ ff_layout_has_available_ds (struct pnfs_layout_segment*) ; 
 scalar_t__ ff_layout_no_fallback_to_mds (struct pnfs_layout_segment*) ; 

bool ff_layout_avoid_mds_available_ds(struct pnfs_layout_segment *lseg)
{
	return ff_layout_no_fallback_to_mds(lseg) ||
	       ff_layout_has_available_ds(lseg);
}