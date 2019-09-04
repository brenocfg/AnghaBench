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
struct TYPE_3__ {scalar_t__ expires; } ;
struct vcc_port {TYPE_1__ tx_timer; int /*<<< orphan*/  removed; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

__attribute__((used)) static void vcc_kick_tx(struct vcc_port *port)
{
	assert_spin_locked(&port->lock);

	if (!timer_pending(&port->tx_timer) && !port->removed) {
		port->tx_timer.expires = (jiffies + 1);
		add_timer(&port->tx_timer);
	}
}