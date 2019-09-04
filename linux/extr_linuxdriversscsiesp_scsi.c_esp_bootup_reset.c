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
typedef  int /*<<< orphan*/  u8 ;
struct esp {int /*<<< orphan*/  config1; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset_dma ) (struct esp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_CFG1 ; 
 int /*<<< orphan*/  ESP_CMD_RS ; 
 int /*<<< orphan*/  ESP_CONFIG1_SRRDISAB ; 
 int /*<<< orphan*/  ESP_INTRPT ; 
 int /*<<< orphan*/  esp_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_reset_esp (struct esp*) ; 
 int /*<<< orphan*/  esp_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct esp*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void esp_bootup_reset(struct esp *esp)
{
	u8 val;

	/* Reset the DMA */
	esp->ops->reset_dma(esp);

	/* Reset the ESP */
	esp_reset_esp(esp);

	/* Reset the SCSI bus, but tell ESP not to generate an irq */
	val = esp_read8(ESP_CFG1);
	val |= ESP_CONFIG1_SRRDISAB;
	esp_write8(val, ESP_CFG1);

	scsi_esp_cmd(esp, ESP_CMD_RS);
	udelay(400);

	esp_write8(esp->config1, ESP_CFG1);

	/* Eat any bitrot in the chip and we are done... */
	esp_read8(ESP_INTRPT);
}