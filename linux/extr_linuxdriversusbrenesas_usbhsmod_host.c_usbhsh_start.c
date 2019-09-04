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
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_mod {int /*<<< orphan*/  irq_sign; int /*<<< orphan*/  irq_sack; int /*<<< orphan*/  irq_dtch; int /*<<< orphan*/  irq_attch; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_fifo_init (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_irq_callback_update (struct usbhs_priv*,struct usbhs_mod*) ; 
 struct usbhs_mod* usbhs_mod_get_current (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_pipe_init (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_sys_host_ctrl (struct usbhs_priv*,int) ; 
 int /*<<< orphan*/  usbhsh_dma_map_ctrl ; 
 struct usb_hcd* usbhsh_hpriv_to_hcd (struct usbhsh_hpriv*) ; 
 int /*<<< orphan*/  usbhsh_irq_attch ; 
 int /*<<< orphan*/  usbhsh_irq_dtch ; 
 int /*<<< orphan*/  usbhsh_irq_setup_ack ; 
 int /*<<< orphan*/  usbhsh_irq_setup_err ; 
 int /*<<< orphan*/  usbhsh_pipe_init_for_host (struct usbhs_priv*) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsh_start(struct usbhs_priv *priv)
{
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	struct usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);
	struct usbhs_mod *mod = usbhs_mod_get_current(priv);
	struct device *dev = usbhs_priv_to_dev(priv);
	int ret;

	/* add hcd */
	ret = usb_add_hcd(hcd, 0, 0);
	if (ret < 0)
		return 0;
	device_wakeup_enable(hcd->self.controller);

	/*
	 * pipe initialize and enable DCP
	 */
	usbhs_fifo_init(priv);
	usbhs_pipe_init(priv,
			usbhsh_dma_map_ctrl);
	usbhsh_pipe_init_for_host(priv);

	/*
	 * system config enble
	 * - HI speed
	 * - host
	 * - usb module
	 */
	usbhs_sys_host_ctrl(priv, 1);

	/*
	 * enable irq callback
	 */
	mod->irq_attch		= usbhsh_irq_attch;
	mod->irq_dtch		= usbhsh_irq_dtch;
	mod->irq_sack		= usbhsh_irq_setup_ack;
	mod->irq_sign		= usbhsh_irq_setup_err;
	usbhs_irq_callback_update(priv, mod);

	dev_dbg(dev, "start host\n");

	return ret;
}