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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ arb_divider; } ;
struct baycom_state {int /*<<< orphan*/  hdrv; TYPE_1__ modem; } ;

/* Variables and functions */
 int /*<<< orphan*/  baycom_int_freq (struct baycom_state*) ; 
 int /*<<< orphan*/  hdlcdrv_arbitrate (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ hdlcdrv_ptt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdlcdrv_receiver (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdlcdrv_transmitter (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 struct baycom_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  par96_rx (struct net_device*,struct baycom_state*) ; 
 int /*<<< orphan*/  par96_tx (struct net_device*,struct baycom_state*) ; 

__attribute__((used)) static void par96_interrupt(void *dev_id)
{
	struct net_device *dev = dev_id;
	struct baycom_state *bc = netdev_priv(dev);

	baycom_int_freq(bc);
	/*
	 * check if transmitter active
	 */
	if (hdlcdrv_ptt(&bc->hdrv))
		par96_tx(dev, bc);
	else {
		par96_rx(dev, bc);
		if (--bc->modem.arb_divider <= 0) {
			bc->modem.arb_divider = 6;
			local_irq_enable();
			hdlcdrv_arbitrate(dev, &bc->hdrv);
		}
	}
	local_irq_enable();
	hdlcdrv_transmitter(dev, &bc->hdrv);
	hdlcdrv_receiver(dev, &bc->hdrv);
        local_irq_disable();
}