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
typedef  int xfs_dir2_off_t ;
typedef  scalar_t__ xfs_dir2_dataptr_t ;

/* Variables and functions */
 int XFS_DIR2_DATA_ALIGN_LOG ; 

__attribute__((used)) static inline xfs_dir2_off_t
xfs_dir2_dataptr_to_byte(xfs_dir2_dataptr_t dp)
{
	return (xfs_dir2_off_t)dp << XFS_DIR2_DATA_ALIGN_LOG;
}