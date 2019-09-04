#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_video_device {TYPE_3__* ops; scalar_t__ field_off; TYPE_2__* cur_frm; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* queue ) (struct vpfe_device*,unsigned long) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_5__ {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vpfe_device*,unsigned long) ; 
 unsigned long vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vpfe_video_schedule_bottom_field(struct vpfe_video_device *video)
{
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	unsigned long addr;

	addr = vb2_dma_contig_plane_dma_addr(&video->cur_frm->vb.vb2_buf, 0);
	addr += video->field_off;
	video->ops->queue(vpfe_dev, addr);
}