#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fc_vport {int dummy; } ;
struct attribute_container {int dummy; } ;
struct TYPE_6__ {struct attribute_container ac; } ;
struct fc_internal {TYPE_1__ vport_attr_cont; } ;
struct device {int dummy; } ;
struct Scsi_Host {TYPE_4__* transportt; } ;
struct TYPE_10__ {int /*<<< orphan*/  class; } ;
struct TYPE_7__ {int /*<<< orphan*/ * class; } ;
struct TYPE_8__ {TYPE_2__ ac; } ;
struct TYPE_9__ {TYPE_3__ host_attrs; } ;

/* Variables and functions */
 struct fc_vport* dev_to_vport (struct device*) ; 
 TYPE_5__ fc_host_class ; 
 int /*<<< orphan*/  scsi_is_fc_vport (struct device*) ; 
 struct fc_internal* to_fc_internal (TYPE_4__*) ; 
 struct Scsi_Host* vport_to_shost (struct fc_vport*) ; 

__attribute__((used)) static int fc_vport_match(struct attribute_container *cont,
			    struct device *dev)
{
	struct fc_vport *vport;
	struct Scsi_Host *shost;
	struct fc_internal *i;

	if (!scsi_is_fc_vport(dev))
		return 0;
	vport = dev_to_vport(dev);

	shost = vport_to_shost(vport);
	if (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &fc_host_class.class)
		return 0;

	i = to_fc_internal(shost->transportt);
	return &i->vport_attr_cont.ac == cont;
}