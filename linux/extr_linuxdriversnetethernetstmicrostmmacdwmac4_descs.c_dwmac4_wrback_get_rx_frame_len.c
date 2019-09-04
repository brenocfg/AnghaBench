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
struct dma_desc {int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int RDES3_PACKET_SIZE_MASK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwmac4_wrback_get_rx_frame_len(struct dma_desc *p, int rx_coe)
{
	return (le32_to_cpu(p->des3) & RDES3_PACKET_SIZE_MASK);
}