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
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_da_state_kill_altpath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_da_state_zone ; 

void
xfs_da_state_free(xfs_da_state_t *state)
{
	xfs_da_state_kill_altpath(state);
#ifdef DEBUG
	memset((char *)state, 0, sizeof(*state));
#endif /* DEBUG */
	kmem_zone_free(xfs_da_state_zone, state);
}