#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sb_frextents; } ;
struct TYPE_7__ {void* m_alloc_set_aside; int /*<<< orphan*/  m_sb_lock; TYPE_1__ m_sb; int /*<<< orphan*/  m_fdblocks; int /*<<< orphan*/  m_ifree; int /*<<< orphan*/  m_icount; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_8__ {int /*<<< orphan*/  freertx; void* freedata; void* freeino; void* allocino; } ;
typedef  TYPE_3__ xfs_fsop_counts_t ;

/* Variables and functions */
 void* percpu_counter_read_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
xfs_fs_counts(
	xfs_mount_t		*mp,
	xfs_fsop_counts_t	*cnt)
{
	cnt->allocino = percpu_counter_read_positive(&mp->m_icount);
	cnt->freeino = percpu_counter_read_positive(&mp->m_ifree);
	cnt->freedata = percpu_counter_read_positive(&mp->m_fdblocks) -
						mp->m_alloc_set_aside;

	spin_lock(&mp->m_sb_lock);
	cnt->freertx = mp->m_sb.sb_frextents;
	spin_unlock(&mp->m_sb_lock);
}