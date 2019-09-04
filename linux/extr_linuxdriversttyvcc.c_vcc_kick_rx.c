#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vio_driver_state {TYPE_1__* vdev; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct vcc_port {TYPE_2__ rx_timer; int /*<<< orphan*/  removed; int /*<<< orphan*/  lock; struct vio_driver_state vio; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_pending (TYPE_2__*) ; 

__attribute__((used)) static void vcc_kick_rx(struct vcc_port *port)
{
	struct vio_driver_state *vio = &port->vio;

	assert_spin_locked(&port->lock);

	if (!timer_pending(&port->rx_timer) && !port->removed) {
		disable_irq_nosync(vio->vdev->rx_irq);
		port->rx_timer.expires = (jiffies + 1);
		add_timer(&port->rx_timer);
	}
}