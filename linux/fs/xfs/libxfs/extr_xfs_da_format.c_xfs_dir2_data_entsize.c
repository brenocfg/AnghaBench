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

/* Variables and functions */
 int XFS_DIR2_DATA_ENTSIZE (int) ; 

__attribute__((used)) static int
xfs_dir2_data_entsize(
	int			n)
{
	return XFS_DIR2_DATA_ENTSIZE(n);
}