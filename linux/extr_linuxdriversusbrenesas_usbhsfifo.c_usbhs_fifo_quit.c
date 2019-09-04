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
struct usbhs_mod {scalar_t__ irq_brdysts; scalar_t__ irq_bempsts; int /*<<< orphan*/ * irq_ready; int /*<<< orphan*/ * irq_empty; } ;

/* Variables and functions */
 struct usbhs_mod* usbhs_mod_get_current (struct usbhs_priv*) ; 

void usbhs_fifo_quit(struct usbhs_priv *priv)
{
	struct usbhs_mod *mod = usbhs_mod_get_current(priv);

	mod->irq_empty		= NULL;
	mod->irq_ready		= NULL;
	mod->irq_bempsts	= 0;
	mod->irq_brdysts	= 0;
}