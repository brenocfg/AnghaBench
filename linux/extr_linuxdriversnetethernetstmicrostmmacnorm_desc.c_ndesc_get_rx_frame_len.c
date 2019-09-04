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
struct dma_desc {int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 unsigned int RDES0_FRAME_LEN_MASK ; 
 unsigned int RDES0_FRAME_LEN_SHIFT ; 
 int STMMAC_RX_COE_TYPE1 ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ndesc_get_rx_frame_len(struct dma_desc *p, int rx_coe_type)
{
	unsigned int csum = 0;

	/* The type-1 checksum offload engines append the checksum at
	 * the end of frame and the two bytes of checksum are added in
	 * the length.
	 * Adjust for that in the framelen for type-1 checksum offload
	 * engines
	 */
	if (rx_coe_type == STMMAC_RX_COE_TYPE1)
		csum = 2;

	return (((le32_to_cpu(p->des0) & RDES0_FRAME_LEN_MASK)
				>> RDES0_FRAME_LEN_SHIFT) -
		csum);

}