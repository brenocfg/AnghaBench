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
struct xfs_mount {int /*<<< orphan*/  m_error_kobj; int /*<<< orphan*/  m_error_meta_kobj; struct xfs_error_cfg** m_error_cfg; } ;
struct xfs_error_cfg {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int XFS_ERR_CLASS_MAX ; 
 int XFS_ERR_ERRNO_MAX ; 
 int /*<<< orphan*/  xfs_sysfs_del (int /*<<< orphan*/ *) ; 

void
xfs_error_sysfs_del(
	struct xfs_mount	*mp)
{
	struct xfs_error_cfg	*cfg;
	int			i, j;

	for (i = 0; i < XFS_ERR_CLASS_MAX; i++) {
		for (j = 0; j < XFS_ERR_ERRNO_MAX; j++) {
			cfg = &mp->m_error_cfg[i][j];

			xfs_sysfs_del(&cfg->kobj);
		}
	}
	xfs_sysfs_del(&mp->m_error_meta_kobj);
	xfs_sysfs_del(&mp->m_error_kobj);
}