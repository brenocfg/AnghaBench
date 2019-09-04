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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int /*<<< orphan*/  irq; scalar_t__* hostdata; } ;
struct NCR_700_Host_Parameters {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCR_700_release (struct Scsi_Host*) ; 
 struct Scsi_Host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct NCR_700_Host_Parameters*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static int snirm710_driver_remove(struct platform_device *dev)
{
	struct Scsi_Host *host = dev_get_drvdata(&dev->dev);
	struct NCR_700_Host_Parameters *hostdata =
		(struct NCR_700_Host_Parameters *)host->hostdata[0];

	scsi_remove_host(host);
	NCR_700_release(host);
	free_irq(host->irq, host);
	iounmap(hostdata->base);
	kfree(hostdata);

	return 0;
}