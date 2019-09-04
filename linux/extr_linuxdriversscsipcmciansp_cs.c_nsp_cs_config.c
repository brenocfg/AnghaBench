#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int config_flags; int /*<<< orphan*/  irq; TYPE_3__** resource; TYPE_1__* priv; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_7__ {struct Scsi_Host* host; } ;
typedef  TYPE_1__ scsi_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  IrqNumber; int /*<<< orphan*/  NumAddress; int /*<<< orphan*/  BaseAddress; } ;
typedef  TYPE_2__ nsp_hw_data ;
struct TYPE_9__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONF_AUTO_AUDIO ; 
 int CONF_AUTO_CHECK_VCC ; 
 int CONF_AUTO_SET_IO ; 
 int CONF_AUTO_SET_IOMEM ; 
 int CONF_AUTO_SET_VPP ; 
 int CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 scalar_t__ free_ports ; 
 int /*<<< orphan*/  nsp_cs_config_check ; 
 int /*<<< orphan*/  nsp_cs_release (struct pcmcia_device*) ; 
 TYPE_2__ nsp_data_base ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct Scsi_Host* nsp_detect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp_driver_template ; 
 scalar_t__ nsphw_init (TYPE_2__*) ; 
 int /*<<< orphan*/  nspintr ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_3__*) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 

__attribute__((used)) static int nsp_cs_config(struct pcmcia_device *link)
{
	int		  ret;
	scsi_info_t	 *info	 = link->priv;
	struct Scsi_Host *host;
	nsp_hw_data      *data = &nsp_data_base;

	nsp_dbg(NSP_DEBUG_INIT, "in");

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_CHECK_VCC |
		CONF_AUTO_SET_VPP | CONF_AUTO_AUDIO | CONF_AUTO_SET_IOMEM |
		CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, nsp_cs_config_check, data);
	if (ret)
		goto cs_failed;

	if (pcmcia_request_irq(link, nspintr))
		goto cs_failed;

	ret = pcmcia_enable_device(link);
	if (ret)
		goto cs_failed;

	if (free_ports) {
		if (link->resource[0]) {
			release_region(link->resource[0]->start,
					resource_size(link->resource[0]));
		}
		if (link->resource[1]) {
			release_region(link->resource[1]->start,
					resource_size(link->resource[1]));
		}
	}

	/* Set port and IRQ */
	data->BaseAddress = link->resource[0]->start;
	data->NumAddress  = resource_size(link->resource[0]);
	data->IrqNumber   = link->irq;

	nsp_dbg(NSP_DEBUG_INIT, "I/O[0x%x+0x%x] IRQ %d",
		data->BaseAddress, data->NumAddress, data->IrqNumber);

	if(nsphw_init(data) == FALSE) {
		goto cs_failed;
	}

	host = nsp_detect(&nsp_driver_template);

	if (host == NULL) {
		nsp_dbg(NSP_DEBUG_INIT, "detect failed");
		goto cs_failed;
	}


	ret = scsi_add_host (host, NULL);
	if (ret)
		goto cs_failed;

	scsi_scan_host(host);

	info->host = host;

	return 0;

 cs_failed:
	nsp_dbg(NSP_DEBUG_INIT, "config fail");
	nsp_cs_release(link);

	return -ENODEV;
}