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
typedef  scalar_t__ u32 ;
struct phy_meson8b_usb2_priv {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 phy_meson8b_usb2_read(struct phy_meson8b_usb2_priv *phy_priv,
				 u32 reg)
{
	return readl(phy_priv->regs + reg);
}