#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {size_t id; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;
struct mpsc_port_info {TYPE_1__ port; int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t MPSC_NUM_CTLRS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  mpsc_drv_get_platform_data (struct mpsc_port_info*,struct platform_device*,size_t) ; 
 int mpsc_drv_map_regs (struct mpsc_port_info*,struct platform_device*) ; 
 int /*<<< orphan*/  mpsc_drv_unmap_regs (struct mpsc_port_info*) ; 
 int mpsc_make_ready (struct mpsc_port_info*) ; 
 struct mpsc_port_info* mpsc_ports ; 
 int /*<<< orphan*/  mpsc_reg ; 
 int /*<<< orphan*/  mpsc_release_port (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int mpsc_drv_probe(struct platform_device *dev)
{
	struct mpsc_port_info *pi;
	int rc;

	dev_dbg(&dev->dev, "mpsc_drv_probe: Adding MPSC %d\n", dev->id);

	if (dev->id >= MPSC_NUM_CTLRS)
		return -ENODEV;

	pi = &mpsc_ports[dev->id];

	rc = mpsc_drv_map_regs(pi, dev);
	if (rc)
		return rc;

	mpsc_drv_get_platform_data(pi, dev, dev->id);
	pi->port.dev = &dev->dev;

	rc = mpsc_make_ready(pi);
	if (rc)
		goto err_unmap;

	spin_lock_init(&pi->tx_lock);
	rc = uart_add_one_port(&mpsc_reg, &pi->port);
	if (rc)
		goto err_relport;

	return 0;
err_relport:
	mpsc_release_port(&pi->port);
err_unmap:
	mpsc_drv_unmap_regs(pi);
	return rc;
}