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
struct xfs_perag {unsigned int pag_sick; unsigned int pag_checked; int /*<<< orphan*/  pag_state_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
xfs_ag_measure_sickness(
	struct xfs_perag	*pag,
	unsigned int		*sick,
	unsigned int		*checked)
{
	spin_lock(&pag->pag_state_lock);
	*sick = pag->pag_sick;
	*checked = pag->pag_checked;
	spin_unlock(&pag->pag_state_lock);
}