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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int /*<<< orphan*/  pipe; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (int /*<<< orphan*/ ) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsf_null_handle(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pkt->pipe);
	struct device *dev = usbhs_priv_to_dev(priv);

	dev_err(dev, "null handler\n");

	return -EINVAL;
}