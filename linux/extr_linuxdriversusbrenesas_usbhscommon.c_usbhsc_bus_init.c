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

/* Variables and functions */
 int /*<<< orphan*/  DVSTCTR ; 
 int /*<<< orphan*/  usbhs_vbus_ctrl (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhsc_bus_init(struct usbhs_priv *priv)
{
	usbhs_write(priv, DVSTCTR, 0);

	usbhs_vbus_ctrl(priv, 0);
}