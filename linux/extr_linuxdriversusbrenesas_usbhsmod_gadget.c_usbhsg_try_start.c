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
typedef  int /*<<< orphan*/  u32 ;
struct usbhsg_uep {TYPE_1__* pipe; } ;
struct usbhsg_gpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_mod {int /*<<< orphan*/  irq_ctrl_stage; int /*<<< orphan*/  irq_dev_state; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct usbhsg_uep* mod_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSG_STATUS_REGISTERD ; 
 int /*<<< orphan*/  USBHSG_STATUS_STARTED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 TYPE_1__* usbhs_dcp_malloc (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_fifo_init (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_irq_callback_update (struct usbhs_priv*,struct usbhs_mod*) ; 
 int /*<<< orphan*/  usbhs_lock (struct usbhs_priv*,unsigned long) ; 
 struct usbhs_mod* usbhs_mod_get_current (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_pipe_config_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbhs_pipe_init (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_sys_function_ctrl (struct usbhs_priv*,int) ; 
 int /*<<< orphan*/  usbhs_unlock (struct usbhs_priv*,unsigned long) ; 
 int /*<<< orphan*/  usbhsg_dma_map_ctrl ; 
 struct usbhsg_uep* usbhsg_gpriv_to_dcp (struct usbhsg_gpriv*) ; 
 int /*<<< orphan*/  usbhsg_irq_ctrl_stage ; 
 int /*<<< orphan*/  usbhsg_irq_dev_state ; 
 struct usbhsg_gpriv* usbhsg_priv_to_gpriv (struct usbhs_priv*) ; 
 scalar_t__ usbhsg_status_has (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsg_status_set (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsg_update_pullup (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsg_try_start(struct usbhs_priv *priv, u32 status)
{
	struct usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	struct usbhsg_uep *dcp = usbhsg_gpriv_to_dcp(gpriv);
	struct usbhs_mod *mod = usbhs_mod_get_current(priv);
	struct device *dev = usbhs_priv_to_dev(priv);
	unsigned long flags;
	int ret = 0;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	usbhsg_status_set(gpriv, status);
	if (!(usbhsg_status_has(gpriv, USBHSG_STATUS_STARTED) &&
	      usbhsg_status_has(gpriv, USBHSG_STATUS_REGISTERD)))
		ret = -1; /* not ready */

	usbhs_unlock(priv, flags);
	/********************  spin unlock ********************/

	if (ret < 0)
		return 0; /* not ready is not error */

	/*
	 * enable interrupt and systems if ready
	 */
	dev_dbg(dev, "start gadget\n");

	/*
	 * pipe initialize and enable DCP
	 */
	usbhs_fifo_init(priv);
	usbhs_pipe_init(priv,
			usbhsg_dma_map_ctrl);

	/* dcp init instead of usbhsg_ep_enable() */
	dcp->pipe		= usbhs_dcp_malloc(priv);
	dcp->pipe->mod_private	= dcp;
	usbhs_pipe_config_update(dcp->pipe, 0, 0, 64);

	/*
	 * system config enble
	 * - HI speed
	 * - function
	 * - usb module
	 */
	usbhs_sys_function_ctrl(priv, 1);
	usbhsg_update_pullup(priv);

	/*
	 * enable irq callback
	 */
	mod->irq_dev_state	= usbhsg_irq_dev_state;
	mod->irq_ctrl_stage	= usbhsg_irq_ctrl_stage;
	usbhs_irq_callback_update(priv, mod);

	return 0;
}