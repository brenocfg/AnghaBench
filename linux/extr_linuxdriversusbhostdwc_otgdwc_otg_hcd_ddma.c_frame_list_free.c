#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * frame_list; int /*<<< orphan*/  frame_list_dma; } ;
typedef  TYPE_1__ dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_DMA_FREE (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_FRLIST_EN_NUM ; 
 struct device* dwc_otg_hcd_to_dev (TYPE_1__*) ; 

__attribute__((used)) static void frame_list_free(dwc_otg_hcd_t * hcd)
{
	struct device *dev = dwc_otg_hcd_to_dev(hcd);

	if (!hcd->frame_list)
		return;

	DWC_DMA_FREE(dev, 4 * MAX_FRLIST_EN_NUM, hcd->frame_list, hcd->frame_list_dma);
	hcd->frame_list = NULL;
}