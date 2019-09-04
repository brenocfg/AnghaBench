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
struct intf_priv {scalar_t__ piorw_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

void r8712_usb_unload_intf_priv(struct intf_priv *pintfpriv)
{
	if (pintfpriv->piorw_urb) {
		usb_kill_urb(pintfpriv->piorw_urb);
		usb_free_urb(pintfpriv->piorw_urb);
	}
}