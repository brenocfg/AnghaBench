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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ dev_speed; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;

/* Variables and functions */
 scalar_t__ DWC_OTG_EP_SPEED_HIGH ; 
 int MAX_DMA_DESC_NUM_GENERIC ; 
 int MAX_DMA_DESC_NUM_HS_ISOC ; 

__attribute__((used)) static uint8_t frame_to_desc_idx(dwc_otg_qh_t * qh, uint16_t frame_idx)
{
	if (qh->dev_speed == DWC_OTG_EP_SPEED_HIGH) {
		/*
		 * Descriptor set(8 descriptors) index
		 * which is 8-aligned.
		 */
		return (frame_idx & ((MAX_DMA_DESC_NUM_HS_ISOC / 8) - 1)) * 8;
	} else {
		return (frame_idx & (MAX_DMA_DESC_NUM_GENERIC - 1));
	}
}