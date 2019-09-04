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
struct vio_driver_state {int dummy; } ;
struct vcc_port {int /*<<< orphan*/  lock; struct vio_driver_state vio; } ;

/* Variables and functions */
 int ECONNRESET ; 
#define  LDC_EVENT_DATA_READY 130 
#define  LDC_EVENT_RESET 129 
#define  LDC_EVENT_UP 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vcc_ldc_read (struct vcc_port*) ; 
 int /*<<< orphan*/  vio_conn_reset (struct vio_driver_state*) ; 
 int /*<<< orphan*/  vio_link_state_change (struct vio_driver_state*,int) ; 

__attribute__((used)) static void vcc_event(void *arg, int event)
{
	struct vio_driver_state *vio;
	struct vcc_port *port;
	unsigned long flags;
	int rv;

	port = arg;
	vio = &port->vio;

	spin_lock_irqsave(&port->lock, flags);

	switch (event) {
	case LDC_EVENT_RESET:
	case LDC_EVENT_UP:
		vio_link_state_change(vio, event);
		break;

	case LDC_EVENT_DATA_READY:
		rv = vcc_ldc_read(port);
		if (rv == -ECONNRESET)
			vio_conn_reset(vio);
		break;

	default:
		pr_err("VCC: unexpected LDC event(%d)\n", event);
	}

	spin_unlock_irqrestore(&port->lock, flags);
}