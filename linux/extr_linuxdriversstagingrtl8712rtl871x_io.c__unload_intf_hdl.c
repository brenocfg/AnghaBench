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
struct intf_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct intf_priv*) ; 
 void r8712_usb_unload_intf_priv (struct intf_priv*) ; 

__attribute__((used)) static void _unload_intf_hdl(struct intf_priv *pintfpriv)
{
	void (*unload_intf_priv)(struct intf_priv *pintfpriv);

	unload_intf_priv = &r8712_usb_unload_intf_priv;
	unload_intf_priv(pintfpriv);
	kfree(pintfpriv);
}