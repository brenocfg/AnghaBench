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
struct TYPE_4__ {int /*<<< orphan*/ * n_bytes; int /*<<< orphan*/ * desc_list; int /*<<< orphan*/  desc_list_dma; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_DMA_FREE (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max_desc_num (TYPE_1__*) ; 

__attribute__((used)) static void desc_list_free(struct device *dev, dwc_otg_qh_t * qh)
{
	if (qh->desc_list) {
		DWC_DMA_FREE(dev, max_desc_num(qh), qh->desc_list,
			     qh->desc_list_dma);
		qh->desc_list = NULL;
	}

	if (qh->n_bytes) {
		DWC_FREE(qh->n_bytes);
		qh->n_bytes = NULL;
	}
}