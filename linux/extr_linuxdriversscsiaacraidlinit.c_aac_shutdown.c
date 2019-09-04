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
struct aac_dev {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aac_shutdown (struct aac_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_block_requests (struct Scsi_Host*) ; 

__attribute__((used)) static void aac_shutdown(struct pci_dev *dev)
{
	struct Scsi_Host *shost = pci_get_drvdata(dev);
	scsi_block_requests(shost);
	__aac_shutdown((struct aac_dev *)shost->hostdata);
}