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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vfio_region_info {int index; unsigned int size; int flags; void* offset; } ;
struct mdev_state {int nr_ports; int /*<<< orphan*/  ops_lock; TYPE_1__* region_info; } ;
struct mdev_device {int dummy; } ;
struct TYPE_2__ {unsigned int size; void* vfio_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MTTY_CONFIG_SPACE_SIZE ; 
 unsigned int MTTY_IO_BAR_SIZE ; 
 void* MTTY_VFIO_PCI_INDEX_TO_OFFSET (int) ; 
#define  VFIO_PCI_BAR0_REGION_INDEX 130 
#define  VFIO_PCI_BAR1_REGION_INDEX 129 
#define  VFIO_PCI_CONFIG_REGION_INDEX 128 
 int VFIO_PCI_NUM_REGIONS ; 
 int VFIO_REGION_INFO_FLAG_READ ; 
 int VFIO_REGION_INFO_FLAG_WRITE ; 
 struct mdev_state* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtty_get_region_info(struct mdev_device *mdev,
			 struct vfio_region_info *region_info,
			 u16 *cap_type_id, void **cap_type)
{
	unsigned int size = 0;
	struct mdev_state *mdev_state;
	u32 bar_index;

	if (!mdev)
		return -EINVAL;

	mdev_state = mdev_get_drvdata(mdev);
	if (!mdev_state)
		return -EINVAL;

	bar_index = region_info->index;
	if (bar_index >= VFIO_PCI_NUM_REGIONS)
		return -EINVAL;

	mutex_lock(&mdev_state->ops_lock);

	switch (bar_index) {
	case VFIO_PCI_CONFIG_REGION_INDEX:
		size = MTTY_CONFIG_SPACE_SIZE;
		break;
	case VFIO_PCI_BAR0_REGION_INDEX:
		size = MTTY_IO_BAR_SIZE;
		break;
	case VFIO_PCI_BAR1_REGION_INDEX:
		if (mdev_state->nr_ports == 2)
			size = MTTY_IO_BAR_SIZE;
		break;
	default:
		size = 0;
		break;
	}

	mdev_state->region_info[bar_index].size = size;
	mdev_state->region_info[bar_index].vfio_offset =
		MTTY_VFIO_PCI_INDEX_TO_OFFSET(bar_index);

	region_info->size = size;
	region_info->offset = MTTY_VFIO_PCI_INDEX_TO_OFFSET(bar_index);
	region_info->flags = VFIO_REGION_INFO_FLAG_READ |
		VFIO_REGION_INFO_FLAG_WRITE;
	mutex_unlock(&mdev_state->ops_lock);
	return 0;
}