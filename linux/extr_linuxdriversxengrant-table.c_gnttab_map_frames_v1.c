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
typedef  int /*<<< orphan*/  xen_pfn_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int arch_gnttab_map_shared (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_max_grant_frames () ; 
 TYPE_1__ gnttab_shared ; 

__attribute__((used)) static int gnttab_map_frames_v1(xen_pfn_t *frames, unsigned int nr_gframes)
{
	int rc;

	rc = arch_gnttab_map_shared(frames, nr_gframes,
				    gnttab_max_grant_frames(),
				    &gnttab_shared.addr);
	BUG_ON(rc);

	return 0;
}