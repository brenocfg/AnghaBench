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
struct stm32_usbphyc_phy {int active; struct stm32_usbphyc* usbphyc; } ;
struct stm32_usbphyc {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 struct stm32_usbphyc_phy* phy_get_drvdata (struct phy*) ; 
 int stm32_usbphyc_pll_disable (struct stm32_usbphyc*) ; 

__attribute__((used)) static int stm32_usbphyc_phy_exit(struct phy *phy)
{
	struct stm32_usbphyc_phy *usbphyc_phy = phy_get_drvdata(phy);
	struct stm32_usbphyc *usbphyc = usbphyc_phy->usbphyc;

	usbphyc_phy->active = false;

	return stm32_usbphyc_pll_disable(usbphyc);
}