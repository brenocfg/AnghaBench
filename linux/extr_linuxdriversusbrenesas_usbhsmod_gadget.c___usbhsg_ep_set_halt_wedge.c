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
struct usbhsg_uep {int dummy; } ;
struct usbhsg_gpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int dummy; } ;
struct usb_ep {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSG_STATUS_WEDGE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_lock (struct usbhs_priv*,unsigned long) ; 
 int /*<<< orphan*/  usbhs_pipe_disable (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_number (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_stall (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_unlock (struct usbhs_priv*,unsigned long) ; 
 struct usbhsg_uep* usbhsg_ep_to_uep (struct usb_ep*) ; 
 struct device* usbhsg_gpriv_to_dev (struct usbhsg_gpriv*) ; 
 struct usbhs_priv* usbhsg_gpriv_to_priv (struct usbhsg_gpriv*) ; 
 int /*<<< orphan*/  usbhsg_pipe_disable (struct usbhsg_uep*) ; 
 int /*<<< orphan*/  usbhsg_status_clr (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsg_status_set (struct usbhsg_gpriv*,int /*<<< orphan*/ ) ; 
 struct usbhsg_gpriv* usbhsg_uep_to_gpriv (struct usbhsg_uep*) ; 
 struct usbhs_pipe* usbhsg_uep_to_pipe (struct usbhsg_uep*) ; 

__attribute__((used)) static int __usbhsg_ep_set_halt_wedge(struct usb_ep *ep, int halt, int wedge)
{
	struct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	struct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	struct usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	struct usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);
	struct device *dev = usbhsg_gpriv_to_dev(gpriv);
	unsigned long flags;

	usbhsg_pipe_disable(uep);

	dev_dbg(dev, "set halt %d (pipe %d)\n",
		halt, usbhs_pipe_number(pipe));

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	if (halt)
		usbhs_pipe_stall(pipe);
	else
		usbhs_pipe_disable(pipe);

	if (halt && wedge)
		usbhsg_status_set(gpriv, USBHSG_STATUS_WEDGE);
	else
		usbhsg_status_clr(gpriv, USBHSG_STATUS_WEDGE);

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	return 0;
}