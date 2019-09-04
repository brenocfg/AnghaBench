#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_inode {int /*<<< orphan*/  d_ops; TYPE_1__* i_mount; } ;
struct xfs_dir2_data_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_dir_geo; } ;

/* Variables and functions */
 void xfs_dir2_data_freescan_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_dir2_data_hdr*,int*) ; 

void
xfs_dir2_data_freescan(
	struct xfs_inode	*dp,
	struct xfs_dir2_data_hdr *hdr,
	int			*loghead)
{
	return xfs_dir2_data_freescan_int(dp->i_mount->m_dir_geo, dp->d_ops,
			hdr, loghead);
}