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
struct TYPE_2__ {int /*<<< orphan*/ * vaddr; scalar_t__ count; int /*<<< orphan*/ * pfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 TYPE_1__ xen_auto_xlat_grant_frames ; 
 int /*<<< orphan*/  xen_unmap (int /*<<< orphan*/ *) ; 

void gnttab_free_auto_xlat_frames(void)
{
	if (!xen_auto_xlat_grant_frames.count)
		return;
	kfree(xen_auto_xlat_grant_frames.pfn);
	xen_unmap(xen_auto_xlat_grant_frames.vaddr);

	xen_auto_xlat_grant_frames.pfn = NULL;
	xen_auto_xlat_grant_frames.count = 0;
	xen_auto_xlat_grant_frames.vaddr = NULL;
}