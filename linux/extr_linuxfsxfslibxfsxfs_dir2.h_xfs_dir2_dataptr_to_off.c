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
typedef  int /*<<< orphan*/  xfs_dir2_dataptr_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct xfs_da_geometry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_dir2_byte_to_off (struct xfs_da_geometry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_dataptr_to_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline xfs_dir2_data_aoff_t
xfs_dir2_dataptr_to_off(struct xfs_da_geometry *geo, xfs_dir2_dataptr_t dp)
{
	return xfs_dir2_byte_to_off(geo, xfs_dir2_dataptr_to_byte(dp));
}