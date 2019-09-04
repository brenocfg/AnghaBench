#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {int device_type; } ;
struct sas_rphy {TYPE_2__ dev; TYPE_1__ identify; scalar_t__ scsi_target_id; } ;
struct sas_port {int /*<<< orphan*/  dev; } ;
struct sas_host_attrs {int /*<<< orphan*/  lock; int /*<<< orphan*/  next_expander_id; } ;
struct sas_expander_device {struct sas_rphy rphy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;
typedef  enum sas_device_type { ____Placeholder_sas_device_type } sas_device_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SAS_EDGE_EXPANDER_DEVICE ; 
 int SAS_FANOUT_EXPANDER_DEVICE ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct sas_expander_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_expander_release ; 
 int /*<<< orphan*/  sas_rphy_initialize (struct sas_rphy*) ; 
 struct sas_host_attrs* to_sas_host_attrs (struct Scsi_Host*) ; 
 int /*<<< orphan*/  transport_setup_device (TYPE_2__*) ; 

struct sas_rphy *sas_expander_alloc(struct sas_port *parent,
				    enum sas_device_type type)
{
	struct Scsi_Host *shost = dev_to_shost(&parent->dev);
	struct sas_expander_device *rdev;
	struct sas_host_attrs *sas_host = to_sas_host_attrs(shost);

	BUG_ON(type != SAS_EDGE_EXPANDER_DEVICE &&
	       type != SAS_FANOUT_EXPANDER_DEVICE);

	rdev = kzalloc(sizeof(*rdev), GFP_KERNEL);
	if (!rdev) {
		return NULL;
	}

	device_initialize(&rdev->rphy.dev);
	rdev->rphy.dev.parent = get_device(&parent->dev);
	rdev->rphy.dev.release = sas_expander_release;
	mutex_lock(&sas_host->lock);
	rdev->rphy.scsi_target_id = sas_host->next_expander_id++;
	mutex_unlock(&sas_host->lock);
	dev_set_name(&rdev->rphy.dev, "expander-%d:%d",
		     shost->host_no, rdev->rphy.scsi_target_id);
	rdev->rphy.identify.device_type = type;
	sas_rphy_initialize(&rdev->rphy);
	transport_setup_device(&rdev->rphy.dev);

	return &rdev->rphy;
}