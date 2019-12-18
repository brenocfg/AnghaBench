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
struct xfs_mount {struct xfs_error_cfg** m_error_cfg; } ;
struct xfs_error_cfg {int dummy; } ;

/* Variables and functions */
#define  EIO 130 
#define  ENODEV 129 
#define  ENOSPC 128 
 size_t XFS_ERR_DEFAULT ; 
 size_t XFS_ERR_EIO ; 
 size_t XFS_ERR_ENODEV ; 
 size_t XFS_ERR_ENOSPC ; 

struct xfs_error_cfg *
xfs_error_get_cfg(
	struct xfs_mount	*mp,
	int			error_class,
	int			error)
{
	struct xfs_error_cfg	*cfg;

	if (error < 0)
		error = -error;

	switch (error) {
	case EIO:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_EIO];
		break;
	case ENOSPC:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_ENOSPC];
		break;
	case ENODEV:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_ENODEV];
		break;
	default:
		cfg = &mp->m_error_cfg[error_class][XFS_ERR_DEFAULT];
		break;
	}

	return cfg;
}