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
struct scsi_cmnd {TYPE_1__* device; } ;
struct esp_target_data {int dummy; } ;
struct esp_cmd_entry {struct scsi_cmnd* cmd; } ;
struct esp {scalar_t__* msg_in; int msg_out_len; int /*<<< orphan*/ * msg_out; int /*<<< orphan*/  host; struct esp_target_data* target; struct esp_cmd_entry* active_cmd; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_CMD_SATN ; 
 scalar_t__ EXTENDED_SDTR ; 
 scalar_t__ EXTENDED_WDTR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MESSAGE_REJECT ; 
 int /*<<< orphan*/  esp_msgin_sdtr (struct esp*,struct esp_target_data*) ; 
 int /*<<< orphan*/  esp_msgin_wdtr (struct esp*,struct esp_target_data*) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void esp_msgin_extended(struct esp *esp)
{
	struct esp_cmd_entry *ent = esp->active_cmd;
	struct scsi_cmnd *cmd = ent->cmd;
	struct esp_target_data *tp;
	int tgt = cmd->device->id;

	tp = &esp->target[tgt];
	if (esp->msg_in[2] == EXTENDED_SDTR) {
		esp_msgin_sdtr(esp, tp);
		return;
	}
	if (esp->msg_in[2] == EXTENDED_WDTR) {
		esp_msgin_wdtr(esp, tp);
		return;
	}

	shost_printk(KERN_INFO, esp->host,
		     "Unexpected extended msg type %x\n", esp->msg_in[2]);

	esp->msg_out[0] = MESSAGE_REJECT;
	esp->msg_out_len = 1;
	scsi_esp_cmd(esp, ESP_CMD_SATN);
}