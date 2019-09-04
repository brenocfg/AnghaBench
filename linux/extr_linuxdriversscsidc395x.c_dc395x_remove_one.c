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
struct pci_dev {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  adapter_uninit (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void dc395x_remove_one(struct pci_dev *dev)
{
	struct Scsi_Host *scsi_host = pci_get_drvdata(dev);
	struct AdapterCtlBlk *acb = (struct AdapterCtlBlk *)(scsi_host->hostdata);

	dprintkdbg(DBG_0, "dc395x_remove_one: acb=%p\n", acb);

	scsi_remove_host(scsi_host);
	adapter_uninit(acb);
	pci_disable_device(dev);
	scsi_host_put(scsi_host);
}