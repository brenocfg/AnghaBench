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
struct TYPE_2__ {scalar_t__ iomode; } ;
struct pnfs_layout_segment {TYPE_1__ pls_range; } ;

/* Variables and functions */
 scalar_t__ IOMODE_RW ; 
 scalar_t__ ff_layout_no_read_on_rw (struct pnfs_layout_segment*) ; 

bool ff_layout_avoid_read_on_rw(struct pnfs_layout_segment *lseg)
{
	return lseg->pls_range.iomode == IOMODE_RW &&
	       ff_layout_no_read_on_rw(lseg);
}