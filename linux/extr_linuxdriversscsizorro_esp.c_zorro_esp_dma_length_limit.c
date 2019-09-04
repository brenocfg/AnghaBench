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
typedef  int u32 ;
struct esp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 zorro_esp_dma_length_limit(struct esp *esp, u32 dma_addr,
					u32 dma_len)
{
	return dma_len > 0xFFFFFF ? 0xFFFFFF : dma_len;
}