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
typedef  int /*<<< orphan*/  xfs_da_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/ * kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_da_state_zone ; 

xfs_da_state_t *
xfs_da_state_alloc(void)
{
	return kmem_zone_zalloc(xfs_da_state_zone, KM_NOFS);
}