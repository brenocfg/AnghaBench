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
struct dwc2_qh {scalar_t__ ep_type; scalar_t__ dev_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_DMA_DESC_NUM_GENERIC ; 
 int /*<<< orphan*/  MAX_DMA_DESC_NUM_HS_ISOC ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 scalar_t__ USB_SPEED_HIGH ; 

__attribute__((used)) static u16 dwc2_max_desc_num(struct dwc2_qh *qh)
{
	return (qh->ep_type == USB_ENDPOINT_XFER_ISOC &&
		qh->dev_speed == USB_SPEED_HIGH) ?
		MAX_DMA_DESC_NUM_HS_ISOC : MAX_DMA_DESC_NUM_GENERIC;
}