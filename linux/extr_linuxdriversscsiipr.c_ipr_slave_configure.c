#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int scsi_level; int no_uld_attach; int no_report_opcodes; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  type; struct ipr_resource_entry* hostdata; TYPE_1__* host; } ;
struct ipr_resource_entry {int /*<<< orphan*/  res_path; TYPE_2__* sata_port; } ;
struct ipr_ioa_cfg {TYPE_3__* host; scalar_t__ sis64; } ;
struct ata_port {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {struct ata_port* ap; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPR_MAX_CMD_PER_ATA_LUN ; 
 int IPR_MAX_RES_PATH_LENGTH ; 
 int /*<<< orphan*/  IPR_VSET_MAX_SECTORS ; 
 int /*<<< orphan*/  IPR_VSET_RW_TIMEOUT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_SPC_3 ; 
 int /*<<< orphan*/  TYPE_RAID ; 
 int /*<<< orphan*/  ata_sas_slave_configure (struct scsi_device*,struct ata_port*) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_format_res_path (struct ipr_ioa_cfg*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ipr_is_af_dasd_device (struct ipr_resource_entry*) ; 
 scalar_t__ ipr_is_gata (struct ipr_resource_entry*) ; 
 scalar_t__ ipr_is_ioa_resource (struct ipr_resource_entry*) ; 
 scalar_t__ ipr_is_vset_device (struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ipr_slave_configure(struct scsi_device *sdev)
{
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *) sdev->host->hostdata;
	struct ipr_resource_entry *res;
	struct ata_port *ap = NULL;
	unsigned long lock_flags = 0;
	char buffer[IPR_MAX_RES_PATH_LENGTH];

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = sdev->hostdata;
	if (res) {
		if (ipr_is_af_dasd_device(res))
			sdev->type = TYPE_RAID;
		if (ipr_is_af_dasd_device(res) || ipr_is_ioa_resource(res)) {
			sdev->scsi_level = 4;
			sdev->no_uld_attach = 1;
		}
		if (ipr_is_vset_device(res)) {
			sdev->scsi_level = SCSI_SPC_3;
			sdev->no_report_opcodes = 1;
			blk_queue_rq_timeout(sdev->request_queue,
					     IPR_VSET_RW_TIMEOUT);
			blk_queue_max_hw_sectors(sdev->request_queue, IPR_VSET_MAX_SECTORS);
		}
		if (ipr_is_gata(res) && res->sata_port)
			ap = res->sata_port->ap;
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

		if (ap) {
			scsi_change_queue_depth(sdev, IPR_MAX_CMD_PER_ATA_LUN);
			ata_sas_slave_configure(sdev, ap);
		}

		if (ioa_cfg->sis64)
			sdev_printk(KERN_INFO, sdev, "Resource path: %s\n",
				    ipr_format_res_path(ioa_cfg,
				res->res_path, buffer, sizeof(buffer)));
		return 0;
	}
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return 0;
}