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
 int DCFM ; 
 int DPRPU ; 
 int DRPD ; 
 int /*<<< orphan*/  DVSTCTR ; 
 int EXTLP ; 
 int HSE ; 
 int PWEN ; 
 int /*<<< orphan*/  SYSCFG ; 
 int USBE ; 
 int has_otg ; 
 int /*<<< orphan*/  usbhs_bset (struct usbhs_priv*,int /*<<< orphan*/ ,int,int) ; 
 int usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

void usbhs_sys_host_ctrl(struct usbhs_priv *priv, int enable)
{
	u16 mask = DCFM | DRPD | DPRPU | HSE | USBE;
	u16 val  = DCFM | DRPD | HSE | USBE;
	int has_otg = usbhs_get_dparam(priv, has_otg);

	if (has_otg)
		usbhs_bset(priv, DVSTCTR, (EXTLP | PWEN), (EXTLP | PWEN));

	/*
	 * if enable
	 *
	 * - select Host mode
	 * - D+ Line/D- Line Pull-down
	 */
	usbhs_bset(priv, SYSCFG, mask, enable ? val : 0);
}