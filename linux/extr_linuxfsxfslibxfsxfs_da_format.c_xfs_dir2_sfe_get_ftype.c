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
typedef  int /*<<< orphan*/  uint8_t ;
struct xfs_dir2_sf_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR3_FT_UNKNOWN ; 

__attribute__((used)) static uint8_t
xfs_dir2_sfe_get_ftype(
	struct xfs_dir2_sf_entry *sfep)
{
	return XFS_DIR3_FT_UNKNOWN;
}