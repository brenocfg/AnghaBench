#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct srp_rport_identifiers {int /*<<< orphan*/  roles; int /*<<< orphan*/  port_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct srp_rport {int reconnect_delay; int fast_io_fail_tmo; int dev_loss_tmo; TYPE_2__ dev; int /*<<< orphan*/  dev_loss_work; int /*<<< orphan*/  fast_io_fail_work; int /*<<< orphan*/  reconnect_work; int /*<<< orphan*/  roles; int /*<<< orphan*/  port_id; int /*<<< orphan*/  mutex; } ;
struct srp_internal {TYPE_1__* f; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; int /*<<< orphan*/  transportt; struct device shost_gendev; } ;
struct TYPE_13__ {int /*<<< orphan*/  next_port_id; } ;
struct TYPE_11__ {int* reconnect_delay; int* fast_io_fail_tmo; int* dev_loss_tmo; scalar_t__ reconnect; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct srp_rport* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 struct srp_rport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rport_dev_loss_timedout ; 
 int /*<<< orphan*/  rport_fast_io_fail_timedout ; 
 int /*<<< orphan*/  srp_reconnect_work ; 
 int /*<<< orphan*/  srp_rport_release ; 
 TYPE_6__* to_srp_host_attrs (struct Scsi_Host*) ; 
 struct srp_internal* to_srp_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_add_device (TYPE_2__*) ; 
 int /*<<< orphan*/  transport_configure_device (TYPE_2__*) ; 
 int /*<<< orphan*/  transport_destroy_device (TYPE_2__*) ; 
 int /*<<< orphan*/  transport_setup_device (TYPE_2__*) ; 

struct srp_rport *srp_rport_add(struct Scsi_Host *shost,
				struct srp_rport_identifiers *ids)
{
	struct srp_rport *rport;
	struct device *parent = &shost->shost_gendev;
	struct srp_internal *i = to_srp_internal(shost->transportt);
	int id, ret;

	rport = kzalloc(sizeof(*rport), GFP_KERNEL);
	if (!rport)
		return ERR_PTR(-ENOMEM);

	mutex_init(&rport->mutex);

	device_initialize(&rport->dev);

	rport->dev.parent = get_device(parent);
	rport->dev.release = srp_rport_release;

	memcpy(rport->port_id, ids->port_id, sizeof(rport->port_id));
	rport->roles = ids->roles;

	if (i->f->reconnect)
		rport->reconnect_delay = i->f->reconnect_delay ?
			*i->f->reconnect_delay : 10;
	INIT_DELAYED_WORK(&rport->reconnect_work, srp_reconnect_work);
	rport->fast_io_fail_tmo = i->f->fast_io_fail_tmo ?
		*i->f->fast_io_fail_tmo : 15;
	rport->dev_loss_tmo = i->f->dev_loss_tmo ? *i->f->dev_loss_tmo : 60;
	INIT_DELAYED_WORK(&rport->fast_io_fail_work,
			  rport_fast_io_fail_timedout);
	INIT_DELAYED_WORK(&rport->dev_loss_work, rport_dev_loss_timedout);

	id = atomic_inc_return(&to_srp_host_attrs(shost)->next_port_id);
	dev_set_name(&rport->dev, "port-%d:%d", shost->host_no, id);

	transport_setup_device(&rport->dev);

	ret = device_add(&rport->dev);
	if (ret) {
		transport_destroy_device(&rport->dev);
		put_device(&rport->dev);
		return ERR_PTR(ret);
	}

	transport_add_device(&rport->dev);
	transport_configure_device(&rport->dev);

	return rport;
}