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
struct xfs_mount {unsigned int m_rt_sick; unsigned int m_rt_checked; int /*<<< orphan*/  m_sb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
xfs_rt_measure_sickness(
	struct xfs_mount	*mp,
	unsigned int		*sick,
	unsigned int		*checked)
{
	spin_lock(&mp->m_sb_lock);
	*sick = mp->m_rt_sick;
	*checked = mp->m_rt_checked;
	spin_unlock(&mp->m_sb_lock);
}