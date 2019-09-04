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
typedef  int u32 ;
struct esp {scalar_t__ dma_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 int ESP_CMD_DMA ; 
 int /*<<< orphan*/  ESP_TCLOW ; 
 int /*<<< orphan*/  ESP_TCMED ; 
 int /*<<< orphan*/  jazz_esp_write8 (struct esp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int) ; 
 int /*<<< orphan*/  vdma_disable (int) ; 
 int /*<<< orphan*/  vdma_enable (int) ; 
 int /*<<< orphan*/  vdma_set_addr (int,int) ; 
 int /*<<< orphan*/  vdma_set_count (int,int) ; 
 int /*<<< orphan*/  vdma_set_mode (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jazz_esp_send_dma_cmd(struct esp *esp, u32 addr, u32 esp_count,
				  u32 dma_count, int write, u8 cmd)
{
	BUG_ON(!(cmd & ESP_CMD_DMA));

	jazz_esp_write8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	jazz_esp_write8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	vdma_disable ((int)esp->dma_regs);
	if (write)
		vdma_set_mode ((int)esp->dma_regs, DMA_MODE_READ);
	else
		vdma_set_mode ((int)esp->dma_regs, DMA_MODE_WRITE);

	vdma_set_addr ((int)esp->dma_regs, addr);
	vdma_set_count ((int)esp->dma_regs, dma_count);
	vdma_enable ((int)esp->dma_regs);

	scsi_esp_cmd(esp, cmd);
}