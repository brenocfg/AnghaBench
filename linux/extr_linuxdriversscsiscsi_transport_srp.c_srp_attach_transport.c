#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  match; int /*<<< orphan*/ * class; int /*<<< orphan*/ ** attrs; } ;
struct TYPE_6__ {TYPE_1__ ac; } ;
struct scsi_transport_template {int host_size; TYPE_2__ host_attrs; } ;
struct srp_internal {struct scsi_transport_template t; struct srp_function_template* f; TYPE_2__ rport_attr_cont; int /*<<< orphan*/ ** rport_attrs; int /*<<< orphan*/ ** host_attrs; } ;
struct srp_host_attrs {int dummy; } ;
struct srp_function_template {scalar_t__ rport_delete; scalar_t__ reconnect; scalar_t__ has_rport_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  class; } ;
struct TYPE_7__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_delete ; 
 int /*<<< orphan*/  dev_attr_dev_loss_tmo ; 
 int /*<<< orphan*/  dev_attr_failed_reconnects ; 
 int /*<<< orphan*/  dev_attr_fast_io_fail_tmo ; 
 int /*<<< orphan*/  dev_attr_port_id ; 
 int /*<<< orphan*/  dev_attr_reconnect_delay ; 
 int /*<<< orphan*/  dev_attr_roles ; 
 int /*<<< orphan*/  dev_attr_state ; 
 struct srp_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ srp_host_class ; 
 int /*<<< orphan*/  srp_host_match ; 
 TYPE_3__ srp_rport_class ; 
 int /*<<< orphan*/  srp_rport_match ; 
 int /*<<< orphan*/  transport_container_register (TYPE_2__*) ; 

struct scsi_transport_template *
srp_attach_transport(struct srp_function_template *ft)
{
	int count;
	struct srp_internal *i;

	i = kzalloc(sizeof(*i), GFP_KERNEL);
	if (!i)
		return NULL;

	i->t.host_size = sizeof(struct srp_host_attrs);
	i->t.host_attrs.ac.attrs = &i->host_attrs[0];
	i->t.host_attrs.ac.class = &srp_host_class.class;
	i->t.host_attrs.ac.match = srp_host_match;
	i->host_attrs[0] = NULL;
	transport_container_register(&i->t.host_attrs);

	i->rport_attr_cont.ac.attrs = &i->rport_attrs[0];
	i->rport_attr_cont.ac.class = &srp_rport_class.class;
	i->rport_attr_cont.ac.match = srp_rport_match;

	count = 0;
	i->rport_attrs[count++] = &dev_attr_port_id;
	i->rport_attrs[count++] = &dev_attr_roles;
	if (ft->has_rport_state) {
		i->rport_attrs[count++] = &dev_attr_state;
		i->rport_attrs[count++] = &dev_attr_fast_io_fail_tmo;
		i->rport_attrs[count++] = &dev_attr_dev_loss_tmo;
	}
	if (ft->reconnect) {
		i->rport_attrs[count++] = &dev_attr_reconnect_delay;
		i->rport_attrs[count++] = &dev_attr_failed_reconnects;
	}
	if (ft->rport_delete)
		i->rport_attrs[count++] = &dev_attr_delete;
	i->rport_attrs[count++] = NULL;
	BUG_ON(count > ARRAY_SIZE(i->rport_attrs));

	transport_container_register(&i->rport_attr_cont);

	i->f = ft;

	return &i->t;
}