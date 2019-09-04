#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct zfcp_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; int /*<<< orphan*/  units; } ;
struct zfcp_adapter {int /*<<< orphan*/  port_list_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ccw_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ kstrtoull (char const*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 struct zfcp_adapter* zfcp_ccw_adapter_by_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_port_shutdown (struct zfcp_port*,int /*<<< orphan*/ ,char*) ; 
 struct zfcp_port* zfcp_get_port_by_wwpn (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_sysfs_port_units_mutex ; 

__attribute__((used)) static ssize_t zfcp_sysfs_port_remove_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);
	struct zfcp_port *port;
	u64 wwpn;
	int retval = -EINVAL;

	if (!adapter)
		return -ENODEV;

	if (kstrtoull(buf, 0, (unsigned long long *) &wwpn))
		goto out;

	port = zfcp_get_port_by_wwpn(adapter, wwpn);
	if (!port)
		goto out;
	else
		retval = 0;

	mutex_lock(&zfcp_sysfs_port_units_mutex);
	if (atomic_read(&port->units) > 0) {
		retval = -EBUSY;
		mutex_unlock(&zfcp_sysfs_port_units_mutex);
		goto out;
	}
	/* port is about to be removed, so no more unit_add */
	atomic_set(&port->units, -1);
	mutex_unlock(&zfcp_sysfs_port_units_mutex);

	write_lock_irq(&adapter->port_list_lock);
	list_del(&port->list);
	write_unlock_irq(&adapter->port_list_lock);

	put_device(&port->dev);

	zfcp_erp_port_shutdown(port, 0, "syprs_1");
	device_unregister(&port->dev);
 out:
	zfcp_ccw_adapter_put(adapter);
	return retval ? retval : (ssize_t) count;
}