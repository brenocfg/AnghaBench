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
typedef  int /*<<< orphan*/  u16 ;
struct vfio_region_info {int index; int size; int flags; int /*<<< orphan*/  offset; } ;
struct ccw_io_region {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VFIO_CCW_CONFIG_REGION_INDEX 128 
 int VFIO_REGION_INFO_FLAG_READ ; 
 int VFIO_REGION_INFO_FLAG_WRITE ; 

__attribute__((used)) static int vfio_ccw_mdev_get_region_info(struct vfio_region_info *info,
					 u16 *cap_type_id,
					 void **cap_type)
{
	switch (info->index) {
	case VFIO_CCW_CONFIG_REGION_INDEX:
		info->offset = 0;
		info->size = sizeof(struct ccw_io_region);
		info->flags = VFIO_REGION_INFO_FLAG_READ
			      | VFIO_REGION_INFO_FLAG_WRITE;
		return 0;
	default:
		return -EINVAL;
	}
}