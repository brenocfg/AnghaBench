#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_3__ {scalar_t__ online; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int /*<<< orphan*/  __twl_shutdown (TYPE_1__*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void twl_shutdown(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev;

	if (!host)
		return;

	tw_dev = (TW_Device_Extension *)host->hostdata;

	if (tw_dev->online) 
		__twl_shutdown(tw_dev);
}