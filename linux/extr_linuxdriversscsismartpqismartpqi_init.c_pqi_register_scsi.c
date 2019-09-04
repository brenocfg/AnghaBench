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
struct pqi_ctrl_info {struct Scsi_Host* scsi_host; int /*<<< orphan*/  ctrl_id; TYPE_1__* pci_dev; int /*<<< orphan*/  num_queue_groups; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  scsi_ml_can_queue; int /*<<< orphan*/  max_sectors; } ;
struct Scsi_Host {int this_id; unsigned long* hostdata; int /*<<< orphan*/  nr_hw_queues; int /*<<< orphan*/  irq; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  transportt; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  can_queue; int /*<<< orphan*/  cmd_per_lun; int /*<<< orphan*/  max_sectors; int /*<<< orphan*/  max_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_cmd_len; int /*<<< orphan*/  max_channel; scalar_t__ n_io_port; scalar_t__ io_port; } ;
typedef  int /*<<< orphan*/  ctrl_info ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  PQI_MAX_BUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pqi_add_sas_host (struct Scsi_Host*,struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_driver_template ; 
 int /*<<< orphan*/  pqi_sas_transport_template ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static int pqi_register_scsi(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	struct Scsi_Host *shost;

	shost = scsi_host_alloc(&pqi_driver_template, sizeof(ctrl_info));
	if (!shost) {
		dev_err(&ctrl_info->pci_dev->dev,
			"scsi_host_alloc failed for controller %u\n",
			ctrl_info->ctrl_id);
		return -ENOMEM;
	}

	shost->io_port = 0;
	shost->n_io_port = 0;
	shost->this_id = -1;
	shost->max_channel = PQI_MAX_BUS;
	shost->max_cmd_len = MAX_COMMAND_SIZE;
	shost->max_lun = ~0;
	shost->max_id = ~0;
	shost->max_sectors = ctrl_info->max_sectors;
	shost->can_queue = ctrl_info->scsi_ml_can_queue;
	shost->cmd_per_lun = shost->can_queue;
	shost->sg_tablesize = ctrl_info->sg_tablesize;
	shost->transportt = pqi_sas_transport_template;
	shost->irq = pci_irq_vector(ctrl_info->pci_dev, 0);
	shost->unique_id = shost->irq;
	shost->nr_hw_queues = ctrl_info->num_queue_groups;
	shost->hostdata[0] = (unsigned long)ctrl_info;

	rc = scsi_add_host(shost, &ctrl_info->pci_dev->dev);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"scsi_add_host failed for controller %u\n",
			ctrl_info->ctrl_id);
		goto free_host;
	}

	rc = pqi_add_sas_host(shost, ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"add SAS host failed for controller %u\n",
			ctrl_info->ctrl_id);
		goto remove_host;
	}

	ctrl_info->scsi_host = shost;

	return 0;

remove_host:
	scsi_remove_host(shost);
free_host:
	scsi_host_put(shost);

	return rc;
}