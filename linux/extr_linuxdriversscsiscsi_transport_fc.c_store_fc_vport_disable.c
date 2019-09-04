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
struct fc_vport {int flags; scalar_t__ vport_state; } ;
struct fc_internal {TYPE_1__* f; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* vport_disable ) (struct fc_vport*,int) ;} ;

/* Variables and functions */
 int EALREADY ; 
 int EBUSY ; 
 int EINVAL ; 
 int FC_VPORT_CREATING ; 
 int FC_VPORT_DEL ; 
 scalar_t__ FC_VPORT_DISABLED ; 
 int stub1 (struct fc_vport*,int) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 
 struct fc_vport* transport_class_to_vport (struct device*) ; 
 struct Scsi_Host* vport_to_shost (struct fc_vport*) ; 

__attribute__((used)) static ssize_t
store_fc_vport_disable(struct device *dev, struct device_attribute *attr,
		       const char *buf,
			   size_t count)
{
	struct fc_vport *vport = transport_class_to_vport(dev);
	struct Scsi_Host *shost = vport_to_shost(vport);
	struct fc_internal *i = to_fc_internal(shost->transportt);
	int stat;

	if (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING))
		return -EBUSY;

	if (*buf == '0') {
		if (vport->vport_state != FC_VPORT_DISABLED)
			return -EALREADY;
	} else if (*buf == '1') {
		if (vport->vport_state == FC_VPORT_DISABLED)
			return -EALREADY;
	} else
		return -EINVAL;

	stat = i->f->vport_disable(vport, ((*buf == '0') ? false : true));
	return stat ? stat : count;
}