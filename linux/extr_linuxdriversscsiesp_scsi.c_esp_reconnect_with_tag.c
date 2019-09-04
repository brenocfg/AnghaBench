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
struct esp_lun_data {struct esp_cmd_entry** tagged_cmds; int /*<<< orphan*/  num_tagged; } ;
struct esp_cmd_entry {int dummy; } ;
struct esp {int sreg; int ireg; int* command_block; int /*<<< orphan*/  host; TYPE_1__* ops; int /*<<< orphan*/  command_block_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_invalidate ) (struct esp*) ;int /*<<< orphan*/  (* dma_drain ) (struct esp*) ;scalar_t__ (* irq_pending ) (struct esp*) ;int /*<<< orphan*/  (* send_dma_cmd ) (struct esp*,int /*<<< orphan*/ ,int,int,int,int) ;} ;

/* Variables and functions */
 int ESP_CMD_DMA ; 
 int /*<<< orphan*/  ESP_CMD_MOK ; 
 int ESP_CMD_TI ; 
 int /*<<< orphan*/  ESP_INTRPT ; 
 int ESP_INTR_DC ; 
 int ESP_INTR_FDONE ; 
 int ESP_MIP ; 
 int ESP_QUICKIRQ_LIMIT ; 
 int ESP_RESELECT_TAG_LIMIT ; 
 int /*<<< orphan*/  ESP_STATUS ; 
 int ESP_STAT_PMASK ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int ORDERED_QUEUE_TAG ; 
 int SIMPLE_QUEUE_TAG ; 
 int /*<<< orphan*/  esp_log_reconnect (char*,...) ; 
 void* esp_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stub1 (struct esp*) ; 
 int /*<<< orphan*/  stub2 (struct esp*,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ stub3 (struct esp*) ; 
 int /*<<< orphan*/  stub4 (struct esp*) ; 
 int /*<<< orphan*/  stub5 (struct esp*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static struct esp_cmd_entry *esp_reconnect_with_tag(struct esp *esp,
						    struct esp_lun_data *lp)
{
	struct esp_cmd_entry *ent;
	int i;

	if (!lp->num_tagged) {
		shost_printk(KERN_ERR, esp->host,
			     "Reconnect w/num_tagged==0\n");
		return NULL;
	}

	esp_log_reconnect("reconnect tag, ");

	for (i = 0; i < ESP_QUICKIRQ_LIMIT; i++) {
		if (esp->ops->irq_pending(esp))
			break;
	}
	if (i == ESP_QUICKIRQ_LIMIT) {
		shost_printk(KERN_ERR, esp->host,
			     "Reconnect IRQ1 timeout\n");
		return NULL;
	}

	esp->sreg = esp_read8(ESP_STATUS);
	esp->ireg = esp_read8(ESP_INTRPT);

	esp_log_reconnect("IRQ(%d:%x:%x), ",
			  i, esp->ireg, esp->sreg);

	if (esp->ireg & ESP_INTR_DC) {
		shost_printk(KERN_ERR, esp->host,
			     "Reconnect, got disconnect.\n");
		return NULL;
	}

	if ((esp->sreg & ESP_STAT_PMASK) != ESP_MIP) {
		shost_printk(KERN_ERR, esp->host,
			     "Reconnect, not MIP sreg[%02x].\n", esp->sreg);
		return NULL;
	}

	/* DMA in the tag bytes... */
	esp->command_block[0] = 0xff;
	esp->command_block[1] = 0xff;
	esp->ops->send_dma_cmd(esp, esp->command_block_dma,
			       2, 2, 1, ESP_CMD_DMA | ESP_CMD_TI);

	/* ACK the message.  */
	scsi_esp_cmd(esp, ESP_CMD_MOK);

	for (i = 0; i < ESP_RESELECT_TAG_LIMIT; i++) {
		if (esp->ops->irq_pending(esp)) {
			esp->sreg = esp_read8(ESP_STATUS);
			esp->ireg = esp_read8(ESP_INTRPT);
			if (esp->ireg & ESP_INTR_FDONE)
				break;
		}
		udelay(1);
	}
	if (i == ESP_RESELECT_TAG_LIMIT) {
		shost_printk(KERN_ERR, esp->host, "Reconnect IRQ2 timeout\n");
		return NULL;
	}
	esp->ops->dma_drain(esp);
	esp->ops->dma_invalidate(esp);

	esp_log_reconnect("IRQ2(%d:%x:%x) tag[%x:%x]\n",
			  i, esp->ireg, esp->sreg,
			  esp->command_block[0],
			  esp->command_block[1]);

	if (esp->command_block[0] < SIMPLE_QUEUE_TAG ||
	    esp->command_block[0] > ORDERED_QUEUE_TAG) {
		shost_printk(KERN_ERR, esp->host,
			     "Reconnect, bad tag type %02x.\n",
			     esp->command_block[0]);
		return NULL;
	}

	ent = lp->tagged_cmds[esp->command_block[1]];
	if (!ent) {
		shost_printk(KERN_ERR, esp->host,
			     "Reconnect, no entry for tag %02x.\n",
			     esp->command_block[1]);
		return NULL;
	}

	return ent;
}