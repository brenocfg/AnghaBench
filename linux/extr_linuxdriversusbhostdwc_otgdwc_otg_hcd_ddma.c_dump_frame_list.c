#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * frame_list; } ;
typedef  TYPE_1__ dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 int MAX_FRLIST_EN_NUM ; 

void dump_frame_list(dwc_otg_hcd_t * hcd)
{
	int i = 0;
	DWC_PRINTF("--FRAME LIST (hex) --\n");
	for (i = 0; i < MAX_FRLIST_EN_NUM; i++) {
		DWC_PRINTF("%x\t", hcd->frame_list[i]);
		if (!(i % 8) && i)
			DWC_PRINTF("\n");
	}
	DWC_PRINTF("\n----\n");

}