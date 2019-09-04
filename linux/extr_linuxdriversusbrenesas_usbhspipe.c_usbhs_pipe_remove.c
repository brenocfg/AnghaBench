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
struct usbhs_pipe_info {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct usbhs_pipe_info* usbhs_priv_to_pipeinfo (struct usbhs_priv*) ; 

void usbhs_pipe_remove(struct usbhs_priv *priv)
{
	struct usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);

	kfree(info->pipe);
}