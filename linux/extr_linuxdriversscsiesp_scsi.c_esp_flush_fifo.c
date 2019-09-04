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
struct esp {scalar_t__ rev; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ ESP236 ; 
 int /*<<< orphan*/  ESP_CMD_FLUSH ; 
 int /*<<< orphan*/  ESP_FFLAGS ; 
 int ESP_FF_FBYTES ; 
 int /*<<< orphan*/  KERN_ALERT ; 
 int esp_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void esp_flush_fifo(struct esp *esp)
{
	scsi_esp_cmd(esp, ESP_CMD_FLUSH);
	if (esp->rev == ESP236) {
		int lim = 1000;

		while (esp_read8(ESP_FFLAGS) & ESP_FF_FBYTES) {
			if (--lim == 0) {
				shost_printk(KERN_ALERT, esp->host,
					     "ESP_FF_BYTES will not clear!\n");
				break;
			}
			udelay(1);
		}
	}
}