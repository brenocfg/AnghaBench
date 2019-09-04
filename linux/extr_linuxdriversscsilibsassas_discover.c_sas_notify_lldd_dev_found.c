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
struct sas_internal {TYPE_1__* dft; } ;
struct TYPE_6__ {struct Scsi_Host* shost; } ;
struct sas_ha_struct {int /*<<< orphan*/  dev; TYPE_3__ core; } ;
struct domain_device {int /*<<< orphan*/  kref; int /*<<< orphan*/  state; int /*<<< orphan*/  sas_addr; TYPE_2__* port; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_5__ {struct sas_ha_struct* ha; } ;
struct TYPE_4__ {int (* lldd_dev_found ) (struct domain_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_DEV_FOUND ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct domain_device*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

int sas_notify_lldd_dev_found(struct domain_device *dev)
{
	int res = 0;
	struct sas_ha_struct *sas_ha = dev->port->ha;
	struct Scsi_Host *shost = sas_ha->core.shost;
	struct sas_internal *i = to_sas_internal(shost->transportt);

	if (!i->dft->lldd_dev_found)
		return 0;

	res = i->dft->lldd_dev_found(dev);
	if (res) {
		printk("sas: driver on pcidev %s cannot handle "
		       "device %llx, error:%d\n",
		       dev_name(sas_ha->dev),
		       SAS_ADDR(dev->sas_addr), res);
	}
	set_bit(SAS_DEV_FOUND, &dev->state);
	kref_get(&dev->kref);
	return res;
}