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
typedef  unsigned int u32 ;
struct esp {scalar_t__ rev; } ;

/* Variables and functions */
 scalar_t__ FASHME ; 

__attribute__((used)) static u32 esp_dma_length_limit(struct esp *esp, u32 dma_addr, u32 dma_len)
{
	if (esp->rev == FASHME) {
		/* Arbitrary segment boundaries, 24-bit counts.  */
		if (dma_len > (1U << 24))
			dma_len = (1U << 24);
	} else {
		u32 base, end;

		/* ESP chip limits other variants by 16-bits of transfer
		 * count.  Actually on FAS100A and FAS236 we could get
		 * 24-bits of transfer count by enabling ESP_CONFIG2_FENAB
		 * in the ESP_CFG2 register but that causes other unwanted
		 * changes so we don't use it currently.
		 */
		if (dma_len > (1U << 16))
			dma_len = (1U << 16);

		/* All of the DMA variants hooked up to these chips
		 * cannot handle crossing a 24-bit address boundary.
		 */
		base = dma_addr & ((1U << 24) - 1U);
		end = base + dma_len;
		if (end > (1U << 24))
			end = (1U <<24);
		dma_len = end - base;
	}
	return dma_len;
}