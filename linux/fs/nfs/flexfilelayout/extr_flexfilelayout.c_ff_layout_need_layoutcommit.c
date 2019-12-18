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
struct pnfs_layout_segment {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int FF_FLAGS_NO_LAYOUTCOMMIT ; 
 TYPE_1__* FF_LAYOUT_LSEG (struct pnfs_layout_segment*) ; 

__attribute__((used)) static bool
ff_layout_need_layoutcommit(struct pnfs_layout_segment *lseg)
{
	return !(FF_LAYOUT_LSEG(lseg)->flags & FF_FLAGS_NO_LAYOUTCOMMIT);
}