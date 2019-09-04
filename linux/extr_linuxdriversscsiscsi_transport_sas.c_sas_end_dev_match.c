#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ device_type; } ;
struct sas_rphy {TYPE_4__ identify; } ;
struct attribute_container {int dummy; } ;
struct TYPE_10__ {struct attribute_container ac; } ;
struct sas_internal {TYPE_3__ end_dev_attr_cont; } ;
struct device {TYPE_5__* parent; } ;
struct Scsi_Host {TYPE_6__* transportt; } ;
struct TYPE_14__ {int /*<<< orphan*/  class; } ;
struct TYPE_8__ {int /*<<< orphan*/ * class; } ;
struct TYPE_9__ {TYPE_1__ ac; } ;
struct TYPE_13__ {TYPE_2__ host_attrs; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ SAS_END_DEVICE ; 
 struct sas_rphy* dev_to_rphy (struct device*) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 TYPE_7__ sas_host_class ; 
 int /*<<< orphan*/  scsi_is_sas_rphy (struct device*) ; 
 struct sas_internal* to_sas_internal (TYPE_6__*) ; 

__attribute__((used)) static int sas_end_dev_match(struct attribute_container *cont,
			     struct device *dev)
{
	struct Scsi_Host *shost;
	struct sas_internal *i;
	struct sas_rphy *rphy;

	if (!scsi_is_sas_rphy(dev))
		return 0;
	shost = dev_to_shost(dev->parent->parent);
	rphy = dev_to_rphy(dev);

	if (!shost->transportt)
		return 0;
	if (shost->transportt->host_attrs.ac.class !=
			&sas_host_class.class)
		return 0;

	i = to_sas_internal(shost->transportt);
	return &i->end_dev_attr_cont.ac == cont &&
		rphy->identify.device_type == SAS_END_DEVICE;
}