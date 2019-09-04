#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  misc; } ;
struct sbp_target_request {TYPE_1__* pg_tbl; TYPE_2__ orb; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_3__ {int /*<<< orphan*/  segment_length; } ;

/* Variables and functions */
 int CMDBLK_ORB_DATA_SIZE (int /*<<< orphan*/ ) ; 
 int CMDBLK_ORB_DIRECTION (int /*<<< orphan*/ ) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbp_calc_data_length_direction(struct sbp_target_request *req,
	u32 *data_len, enum dma_data_direction *data_dir)
{
	int data_size, direction, idx;

	data_size = CMDBLK_ORB_DATA_SIZE(be32_to_cpu(req->orb.misc));
	direction = CMDBLK_ORB_DIRECTION(be32_to_cpu(req->orb.misc));

	if (!data_size) {
		*data_len = 0;
		*data_dir = DMA_NONE;
		return;
	}

	*data_dir = direction ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	if (req->pg_tbl) {
		*data_len = 0;
		for (idx = 0; idx < data_size; idx++) {
			*data_len += be16_to_cpu(
					req->pg_tbl[idx].segment_length);
		}
	} else {
		*data_len = data_size;
	}
}