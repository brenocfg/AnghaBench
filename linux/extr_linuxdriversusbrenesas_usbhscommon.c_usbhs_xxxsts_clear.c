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

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_size ; 
 int /*<<< orphan*/  usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int,int) ; 

void usbhs_xxxsts_clear(struct usbhs_priv *priv, u16 sts_reg, u16 bit)
{
	u16 pipe_mask = (u16)GENMASK(usbhs_get_dparam(priv, pipe_size), 0);

	usbhs_write(priv, sts_reg, ~(1 << bit) & pipe_mask);
}