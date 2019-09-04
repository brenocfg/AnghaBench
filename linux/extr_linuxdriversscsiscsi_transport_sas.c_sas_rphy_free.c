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
struct device {TYPE_1__* parent; } ;
struct sas_rphy {int /*<<< orphan*/  list; struct device dev; } ;
struct sas_host_attrs {int /*<<< orphan*/  lock; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct sas_host_attrs* to_sas_host_attrs (struct Scsi_Host*) ; 
 int /*<<< orphan*/  transport_destroy_device (struct device*) ; 

void sas_rphy_free(struct sas_rphy *rphy)
{
	struct device *dev = &rphy->dev;
	struct Scsi_Host *shost = dev_to_shost(rphy->dev.parent->parent);
	struct sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	mutex_lock(&sas_host->lock);
	list_del(&rphy->list);
	mutex_unlock(&sas_host->lock);

	transport_destroy_device(dev);

	put_device(dev);
}