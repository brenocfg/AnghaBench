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
struct dma_desc {int /*<<< orphan*/  des1; } ;

/* Variables and functions */
 int BUF_SIZE_2KiB ; 
 int RDES1_BUFFER2_SIZE_MASK ; 
 int RDES1_BUFFER2_SIZE_SHIFT ; 
 int RDES1_END_RING ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline void ndesc_rx_set_on_ring(struct dma_desc *p, int end)
{
	p->des1 |= cpu_to_le32(((BUF_SIZE_2KiB - 1)
				<< RDES1_BUFFER2_SIZE_SHIFT)
		    & RDES1_BUFFER2_SIZE_MASK);

	if (end)
		p->des1 |= cpu_to_le32(RDES1_END_RING);
}