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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ DWC_OTG_EP_SPEED_HIGH ; 
 int MAX_DMA_DESC_NUM_GENERIC ; 
 int MAX_DMA_DESC_NUM_HS_ISOC ; 

__attribute__((used)) static inline uint16_t desclist_idx_inc(uint16_t idx, uint16_t inc, uint8_t speed)
{
	return (idx + inc) &
	    (((speed ==
	       DWC_OTG_EP_SPEED_HIGH) ? MAX_DMA_DESC_NUM_HS_ISOC :
	      MAX_DMA_DESC_NUM_GENERIC) - 1);
}