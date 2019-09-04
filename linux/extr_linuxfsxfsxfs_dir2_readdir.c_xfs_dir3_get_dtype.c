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
typedef  size_t uint8_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 unsigned char DT_UNKNOWN ; 
 size_t XFS_DIR3_FT_MAX ; 
 unsigned char* xfs_dir3_filetype_table ; 
 int /*<<< orphan*/  xfs_sb_version_hasftype (int /*<<< orphan*/ *) ; 

unsigned char
xfs_dir3_get_dtype(
	struct xfs_mount	*mp,
	uint8_t			filetype)
{
	if (!xfs_sb_version_hasftype(&mp->m_sb))
		return DT_UNKNOWN;

	if (filetype >= XFS_DIR3_FT_MAX)
		return DT_UNKNOWN;

	return xfs_dir3_filetype_table[filetype];
}