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
struct TYPE_2__ {int /*<<< orphan*/  iomode; } ;
struct pnfs_layout_segment {TYPE_1__ pls_range; int /*<<< orphan*/  pls_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnfs_layout_io_set_failed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pnfs_set_lo_fail(struct pnfs_layout_segment *lseg)
{
	pnfs_layout_io_set_failed(lseg->pls_layout, lseg->pls_range.iomode);
}