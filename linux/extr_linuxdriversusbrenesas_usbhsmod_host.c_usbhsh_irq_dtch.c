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
struct TYPE_2__ {int /*<<< orphan*/  irq_attch; } ;
struct usbhsh_hpriv {TYPE_1__ mod; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_irq_state {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  usbhs_irq_callback_update (struct usbhs_priv*,TYPE_1__*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsh_irq_attch ; 
 int /*<<< orphan*/  usbhsh_port_stat_clear (struct usbhsh_hpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsh_port_stat_set (struct usbhsh_hpriv*,int) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsh_queue_force_pop_all (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsh_irq_dtch(struct usbhs_priv *priv,
			   struct usbhs_irq_state *irq_state)
{
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	struct device *dev = usbhs_priv_to_dev(priv);

	dev_dbg(dev, "device detached\n");

	usbhsh_port_stat_clear(hpriv, USB_PORT_STAT_CONNECTION);
	usbhsh_port_stat_set(hpriv, USB_PORT_STAT_C_CONNECTION << 16);

	/*
	 * enable attch interrupt again
	 *
	 * usbhsh_is_running() becomes invalid
	 * according to this process.
	 * see
	 *	usbhsh_is_running()
	 *	usbhsh_urb_enqueue()
	 */
	hpriv->mod.irq_attch = usbhsh_irq_attch;
	usbhs_irq_callback_update(priv, &hpriv->mod);

	/*
	 * usbhsh_queue_force_pop_all() should be called
	 * after usbhsh_is_running() becomes invalid.
	 */
	usbhsh_queue_force_pop_all(priv);

	return 0;
}