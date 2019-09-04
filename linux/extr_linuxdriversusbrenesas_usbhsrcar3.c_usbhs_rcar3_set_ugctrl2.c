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
typedef  int u32 ;
struct usbhs_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UGCTRL2 ; 
 int UGCTRL2_RESERVED_3 ; 
 int /*<<< orphan*/  usbhs_write32 (struct usbhs_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usbhs_rcar3_set_ugctrl2(struct usbhs_priv *priv, u32 val)
{
	usbhs_write32(priv, UGCTRL2, val | UGCTRL2_RESERVED_3);
}