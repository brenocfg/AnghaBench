#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobject; } ;
struct xfs_mount {TYPE_1__ m_error_kobj; int /*<<< orphan*/  m_error_meta_kobj; int /*<<< orphan*/  m_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ERR_METADATA ; 
 int /*<<< orphan*/  fail_at_unmount ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_error_ktype ; 
 int /*<<< orphan*/  xfs_error_meta_init ; 
 int xfs_error_sysfs_init_class (struct xfs_mount*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sysfs_del (TYPE_1__*) ; 
 int xfs_sysfs_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int
xfs_error_sysfs_init(
	struct xfs_mount	*mp)
{
	int			error;

	/* .../xfs/<dev>/error/ */
	error = xfs_sysfs_init(&mp->m_error_kobj, &xfs_error_ktype,
				&mp->m_kobj, "error");
	if (error)
		return error;

	error = sysfs_create_file(&mp->m_error_kobj.kobject,
				  ATTR_LIST(fail_at_unmount));

	if (error)
		goto out_error;

	/* .../xfs/<dev>/error/metadata/ */
	error = xfs_error_sysfs_init_class(mp, XFS_ERR_METADATA,
				"metadata", &mp->m_error_meta_kobj,
				xfs_error_meta_init);
	if (error)
		goto out_error;

	return 0;

out_error:
	xfs_sysfs_del(&mp->m_error_kobj);
	return error;
}