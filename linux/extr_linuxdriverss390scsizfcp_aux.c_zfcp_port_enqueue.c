#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/  groups; int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {struct zfcp_port* port; struct zfcp_adapter* adapter; } ;
struct zfcp_port {int d_id; int /*<<< orphan*/  status; int /*<<< orphan*/  list; TYPE_3__ dev; TYPE_2__ erp_action; int /*<<< orphan*/  rport_task; scalar_t__ wwpn; struct zfcp_adapter* adapter; int /*<<< orphan*/  rport_work; int /*<<< orphan*/  test_link_work; int /*<<< orphan*/  gid_pn_work; int /*<<< orphan*/  units; int /*<<< orphan*/  unit_list; int /*<<< orphan*/  unit_list_lock; } ;
struct zfcp_adapter {int /*<<< orphan*/  port_list_lock; int /*<<< orphan*/  port_list; TYPE_1__* ccw_device; int /*<<< orphan*/  ref; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct zfcp_port* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPORT_NONE ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_set_name (TYPE_3__*,char*,unsigned long long) ; 
 scalar_t__ device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct zfcp_port*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct zfcp_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_link_test_work ; 
 int /*<<< orphan*/  zfcp_fc_port_did_lookup ; 
 struct zfcp_port* zfcp_get_port_by_wwpn (struct zfcp_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  zfcp_port_attr_groups ; 
 int /*<<< orphan*/  zfcp_port_release ; 
 int /*<<< orphan*/  zfcp_scsi_rport_work ; 

struct zfcp_port *zfcp_port_enqueue(struct zfcp_adapter *adapter, u64 wwpn,
				     u32 status, u32 d_id)
{
	struct zfcp_port *port;
	int retval = -ENOMEM;

	kref_get(&adapter->ref);

	port = zfcp_get_port_by_wwpn(adapter, wwpn);
	if (port) {
		put_device(&port->dev);
		retval = -EEXIST;
		goto err_out;
	}

	port = kzalloc(sizeof(struct zfcp_port), GFP_KERNEL);
	if (!port)
		goto err_out;

	rwlock_init(&port->unit_list_lock);
	INIT_LIST_HEAD(&port->unit_list);
	atomic_set(&port->units, 0);

	INIT_WORK(&port->gid_pn_work, zfcp_fc_port_did_lookup);
	INIT_WORK(&port->test_link_work, zfcp_fc_link_test_work);
	INIT_WORK(&port->rport_work, zfcp_scsi_rport_work);

	port->adapter = adapter;
	port->d_id = d_id;
	port->wwpn = wwpn;
	port->rport_task = RPORT_NONE;
	port->dev.parent = &adapter->ccw_device->dev;
	port->dev.groups = zfcp_port_attr_groups;
	port->dev.release = zfcp_port_release;

	port->erp_action.adapter = adapter;
	port->erp_action.port = port;

	if (dev_set_name(&port->dev, "0x%016llx", (unsigned long long)wwpn)) {
		kfree(port);
		goto err_out;
	}
	retval = -EINVAL;

	if (device_register(&port->dev)) {
		put_device(&port->dev);
		goto err_out;
	}

	write_lock_irq(&adapter->port_list_lock);
	list_add_tail(&port->list, &adapter->port_list);
	write_unlock_irq(&adapter->port_list_lock);

	atomic_or(status | ZFCP_STATUS_COMMON_RUNNING, &port->status);

	return port;

err_out:
	zfcp_ccw_adapter_put(adapter);
	return ERR_PTR(retval);
}