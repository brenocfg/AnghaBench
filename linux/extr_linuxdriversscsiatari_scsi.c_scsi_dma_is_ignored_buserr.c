#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long addr; unsigned long size; } ;

/* Variables and functions */
 unsigned long SCSI_DMA_READ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_addr ; 
 TYPE_1__* m68k_memory ; 
 int m68k_num_memory ; 

__attribute__((used)) static int scsi_dma_is_ignored_buserr(unsigned char dma_stat)
{
	int i;
	unsigned long addr = SCSI_DMA_READ_P(dma_addr), end_addr;

	if (dma_stat & 0x01) {

		/* A bus error happens when DMA-ing from the last page of a
		 * physical memory chunk (DMA prefetch!), but that doesn't hurt.
		 * Check for this case:
		 */

		for (i = 0; i < m68k_num_memory; ++i) {
			end_addr = m68k_memory[i].addr + m68k_memory[i].size;
			if (end_addr <= addr && addr <= end_addr + 4)
				return 1;
		}
	}
	return 0;
}