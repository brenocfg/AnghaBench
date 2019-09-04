#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sas_rphy {int /*<<< orphan*/  scsi_target_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct sas_phy {int number; int enabled; TYPE_1__ dev; int /*<<< orphan*/  port_siblings; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int,...) ; 
 struct sas_rphy* dev_to_rphy (struct device*) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 struct sas_phy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_phy_release ; 
 scalar_t__ scsi_is_sas_expander_device (struct device*) ; 
 int /*<<< orphan*/  transport_setup_device (TYPE_1__*) ; 

struct sas_phy *sas_phy_alloc(struct device *parent, int number)
{
	struct Scsi_Host *shost = dev_to_shost(parent);
	struct sas_phy *phy;

	phy = kzalloc(sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return NULL;

	phy->number = number;
	phy->enabled = 1;

	device_initialize(&phy->dev);
	phy->dev.parent = get_device(parent);
	phy->dev.release = sas_phy_release;
	INIT_LIST_HEAD(&phy->port_siblings);
	if (scsi_is_sas_expander_device(parent)) {
		struct sas_rphy *rphy = dev_to_rphy(parent);
		dev_set_name(&phy->dev, "phy-%d:%d:%d", shost->host_no,
			rphy->scsi_target_id, number);
	} else
		dev_set_name(&phy->dev, "phy-%d:%d", shost->host_no, number);

	transport_setup_device(&phy->dev);

	return phy;
}