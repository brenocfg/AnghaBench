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
typedef  int u8 ;
struct scsi_device {int id; int lun; scalar_t__ scsi_level; } ;
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; struct scsi_device* device; } ;
struct esp_cmd_entry {int /*<<< orphan*/  sense_ptr; int /*<<< orphan*/  saved_sense_ptr; int /*<<< orphan*/  sense_dma; struct scsi_cmnd* cmd; } ;
struct esp {int* command_block; scalar_t__ rev; int /*<<< orphan*/  select_state; scalar_t__ msg_out_len; struct esp_cmd_entry* active_cmd; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* map_single ) (struct esp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ESP_BUSID ; 
 int ESP_BUSID_CTR32BIT ; 
 int ESP_BUSID_RESELID ; 
 int /*<<< orphan*/  ESP_CMD_SELA ; 
 int /*<<< orphan*/  ESP_SELECT_BASIC ; 
 scalar_t__ FASHME ; 
 int /*<<< orphan*/  IDENTIFY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REQUEST_SENSE ; 
 scalar_t__ SCSI_2 ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  esp_log_autosense (char*,int,int) ; 
 int /*<<< orphan*/  esp_send_dma_cmd (struct esp*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_write8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_write_tgt_config3 (struct esp*,int) ; 
 int /*<<< orphan*/  esp_write_tgt_sync (struct esp*,int) ; 
 int /*<<< orphan*/  stub1 (struct esp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_autosense(struct esp *esp, struct esp_cmd_entry *ent)
{
	struct scsi_cmnd *cmd = ent->cmd;
	struct scsi_device *dev = cmd->device;
	int tgt, lun;
	u8 *p, val;

	tgt = dev->id;
	lun = dev->lun;


	if (!ent->sense_ptr) {
		esp_log_autosense("Doing auto-sense for tgt[%d] lun[%d]\n",
				  tgt, lun);

		ent->sense_ptr = cmd->sense_buffer;
		ent->sense_dma = esp->ops->map_single(esp,
						      ent->sense_ptr,
						      SCSI_SENSE_BUFFERSIZE,
						      DMA_FROM_DEVICE);
	}
	ent->saved_sense_ptr = ent->sense_ptr;

	esp->active_cmd = ent;

	p = esp->command_block;
	esp->msg_out_len = 0;

	*p++ = IDENTIFY(0, lun);
	*p++ = REQUEST_SENSE;
	*p++ = ((dev->scsi_level <= SCSI_2) ?
		(lun << 5) : 0);
	*p++ = 0;
	*p++ = 0;
	*p++ = SCSI_SENSE_BUFFERSIZE;
	*p++ = 0;

	esp->select_state = ESP_SELECT_BASIC;

	val = tgt;
	if (esp->rev == FASHME)
		val |= ESP_BUSID_RESELID | ESP_BUSID_CTR32BIT;
	esp_write8(val, ESP_BUSID);

	esp_write_tgt_sync(esp, tgt);
	esp_write_tgt_config3(esp, tgt);

	val = (p - esp->command_block);

	esp_send_dma_cmd(esp, val, 16, ESP_CMD_SELA);
}