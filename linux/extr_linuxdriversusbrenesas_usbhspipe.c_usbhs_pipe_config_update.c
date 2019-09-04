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
typedef  int u16 ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int maxp; } ;
struct renesas_usbhs_driver_pipe_config {scalar_t__ double_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DBLB ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 int usbhs_pipe_number (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct renesas_usbhs_driver_pipe_config* usbhsp_get_pipe_config (struct usbhs_priv*,int) ; 
 int /*<<< orphan*/  usbhsp_pipe_barrier (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_pipe_cfg_set (struct usbhs_pipe*,int,int) ; 
 int /*<<< orphan*/  usbhsp_pipe_maxp_set (struct usbhs_pipe*,int,int) ; 
 int /*<<< orphan*/  usbhsp_pipe_select (struct usbhs_pipe*) ; 

void usbhs_pipe_config_update(struct usbhs_pipe *pipe, u16 devsel,
			      u16 epnum, u16 maxp)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	int pipe_num = usbhs_pipe_number(pipe);
	struct renesas_usbhs_driver_pipe_config *pipe_config =
					usbhsp_get_pipe_config(priv, pipe_num);
	u16 dblb = pipe_config->double_buf ? DBLB : 0;

	if (devsel > 0xA) {
		struct device *dev = usbhs_priv_to_dev(priv);

		dev_err(dev, "devsel error %d\n", devsel);

		devsel = 0;
	}

	usbhsp_pipe_barrier(pipe);

	pipe->maxp = maxp;

	usbhsp_pipe_select(pipe);
	usbhsp_pipe_maxp_set(pipe, 0xFFFF,
			     (devsel << 12) |
			     maxp);

	if (!usbhs_pipe_is_dcp(pipe))
		usbhsp_pipe_cfg_set(pipe,  0x000F | DBLB, epnum | dblb);
}