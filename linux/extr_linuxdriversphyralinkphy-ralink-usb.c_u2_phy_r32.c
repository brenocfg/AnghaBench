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
struct ralink_usb_phy {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 u2_phy_r32(struct ralink_usb_phy *phy, u32 reg)
{
	return readl(phy->base + reg);
}