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
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCPL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  usbhs_mod_is_host (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_pipe_enable (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_pipectrl_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usbhs_dcp_control_transfer_done(struct usbhs_pipe *pipe)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	WARN_ON(!usbhs_pipe_is_dcp(pipe));

	usbhs_pipe_enable(pipe);

	if (!usbhs_mod_is_host(priv)) /* funconly */
		usbhsp_pipectrl_set(pipe, CCPL, CCPL);
}