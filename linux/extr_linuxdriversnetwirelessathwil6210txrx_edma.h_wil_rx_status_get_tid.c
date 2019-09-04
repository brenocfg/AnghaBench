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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int WIL_RX_EDMA_DLPF_LU_MISS_BIT ; 
 int WIL_RX_EDMA_DLPF_LU_MISS_CID_TID_MASK ; 
 int WIL_RX_EDMA_DLPF_LU_MISS_TID_POS ; 
 int wil_rx_status_get_flow_id (void*) ; 

__attribute__((used)) static inline u8 wil_rx_status_get_tid(void *msg)
{
	u16 val = wil_rx_status_get_flow_id(msg);

	if (val & WIL_RX_EDMA_DLPF_LU_MISS_BIT)
		/* TID is in bits 5..7 */
		return (val >> WIL_RX_EDMA_DLPF_LU_MISS_TID_POS) &
			WIL_RX_EDMA_DLPF_LU_MISS_CID_TID_MASK;
	else
		/* TID is in bits 0..3 */
		return val & WIL_RX_EDMA_DLPF_LU_MISS_CID_TID_MASK;
}