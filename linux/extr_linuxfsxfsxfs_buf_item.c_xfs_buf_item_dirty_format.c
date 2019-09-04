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
struct xfs_buf_log_item {int bli_format_count; TYPE_1__* bli_formats; } ;
struct TYPE_2__ {int /*<<< orphan*/  blf_map_size; int /*<<< orphan*/  blf_data_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
xfs_buf_item_dirty_format(
	struct xfs_buf_log_item	*bip)
{
	int			i;

	for (i = 0; i < bip->bli_format_count; i++) {
		if (!xfs_bitmap_empty(bip->bli_formats[i].blf_data_map,
			     bip->bli_formats[i].blf_map_size))
			return true;
	}

	return false;
}