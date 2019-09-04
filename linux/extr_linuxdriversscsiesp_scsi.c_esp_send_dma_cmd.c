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
struct esp {int flags; scalar_t__ rev; int /*<<< orphan*/  command_block_dma; TYPE_1__* ops; int /*<<< orphan*/ * command_block; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_dma_cmd ) (struct esp*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ESP_CMD_DMA ; 
 int ESP_CMD_FLUSH ; 
 int /*<<< orphan*/  ESP_FDATA ; 
 int ESP_FLAG_USE_FIFO ; 
 scalar_t__ FASHME ; 
 int /*<<< orphan*/  esp_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int) ; 
 int /*<<< orphan*/  stub1 (struct esp*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void esp_send_dma_cmd(struct esp *esp, int len, int max_len, int cmd)
{
	if (esp->flags & ESP_FLAG_USE_FIFO) {
		int i;

		scsi_esp_cmd(esp, ESP_CMD_FLUSH);
		for (i = 0; i < len; i++)
			esp_write8(esp->command_block[i], ESP_FDATA);
		scsi_esp_cmd(esp, cmd);
	} else {
		if (esp->rev == FASHME)
			scsi_esp_cmd(esp, ESP_CMD_FLUSH);
		cmd |= ESP_CMD_DMA;
		esp->ops->send_dma_cmd(esp, esp->command_block_dma,
				       len, max_len, 0, cmd);
	}
}