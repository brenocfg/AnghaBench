#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  timer; } ;
struct isci_port {TYPE_4__ timer; } ;
struct TYPE_18__ {int /*<<< orphan*/  timer; } ;
struct isci_phy {TYPE_5__ sata_timer; } ;
struct TYPE_13__ {int /*<<< orphan*/  timer; } ;
struct TYPE_12__ {int /*<<< orphan*/  timer; } ;
struct TYPE_21__ {int /*<<< orphan*/  timer; } ;
struct TYPE_22__ {TYPE_8__ timer; } ;
struct TYPE_19__ {int /*<<< orphan*/  timer; } ;
struct TYPE_20__ {TYPE_6__ timer; } ;
struct isci_host {int logical_port_entries; TYPE_11__ phy_timer; TYPE_10__ timer; TYPE_9__ power_control; TYPE_7__ port_agent; struct isci_phy* phys; struct isci_port* ports; int /*<<< orphan*/  scic_lock; TYPE_3__* scu_registers; int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  interface_control; int /*<<< orphan*/ * output_data_select; } ;
struct TYPE_15__ {TYPE_1__ sgpio; } ;
struct TYPE_16__ {TYPE_2__ peg0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IHOST_STOP_PENDING ; 
 int /*<<< orphan*/  SCIC_CONTROLLER_STOP_TIMEOUT ; 
 int SCI_MAX_PHYS ; 
 int /*<<< orphan*/  SGPIO_HW_CONTROL ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int isci_gpio_count (struct isci_host*) ; 
 int /*<<< orphan*/  sci_controller_reset (struct isci_host*) ; 
 int /*<<< orphan*/  sci_controller_stop (struct isci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_controller_stop_phys (struct isci_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_stop (struct isci_host*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void isci_host_deinit(struct isci_host *ihost)
{
	int i;

	/* disable output data selects */
	for (i = 0; i < isci_gpio_count(ihost); i++)
		writel(SGPIO_HW_CONTROL, &ihost->scu_registers->peg0.sgpio.output_data_select[i]);

	set_bit(IHOST_STOP_PENDING, &ihost->flags);

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_stop(ihost, SCIC_CONTROLLER_STOP_TIMEOUT);
	spin_unlock_irq(&ihost->scic_lock);

	wait_for_stop(ihost);

	/* phy stop is after controller stop to allow port and device to
	 * go idle before shutting down the phys, but the expectation is
	 * that i/o has been shut off well before we reach this
	 * function.
	 */
	sci_controller_stop_phys(ihost);

	/* disable sgpio: where the above wait should give time for the
	 * enclosure to sample the gpios going inactive
	 */
	writel(0, &ihost->scu_registers->peg0.sgpio.interface_control);

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_reset(ihost);
	spin_unlock_irq(&ihost->scic_lock);

	/* Cancel any/all outstanding port timers */
	for (i = 0; i < ihost->logical_port_entries; i++) {
		struct isci_port *iport = &ihost->ports[i];
		del_timer_sync(&iport->timer.timer);
	}

	/* Cancel any/all outstanding phy timers */
	for (i = 0; i < SCI_MAX_PHYS; i++) {
		struct isci_phy *iphy = &ihost->phys[i];
		del_timer_sync(&iphy->sata_timer.timer);
	}

	del_timer_sync(&ihost->port_agent.timer.timer);

	del_timer_sync(&ihost->power_control.timer.timer);

	del_timer_sync(&ihost->timer.timer);

	del_timer_sync(&ihost->phy_timer.timer);
}