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
struct xfs_mount {int /*<<< orphan*/  m_fdblocks; int /*<<< orphan*/  m_ifree; int /*<<< orphan*/  m_icount; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_destroy_percpu_counters(
	struct xfs_mount	*mp)
{
	percpu_counter_destroy(&mp->m_icount);
	percpu_counter_destroy(&mp->m_ifree);
	percpu_counter_destroy(&mp->m_fdblocks);
}