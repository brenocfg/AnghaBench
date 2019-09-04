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
struct rtl_fw {int dummy; } ;
struct rtl8169_private {struct rtl_fw* rtl_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct rtl_fw*) ; 
 int /*<<< orphan*/  rtl_phy_write_fw (struct rtl8169_private*,struct rtl_fw*) ; 

__attribute__((used)) static void rtl_apply_firmware(struct rtl8169_private *tp)
{
	struct rtl_fw *rtl_fw = tp->rtl_fw;

	/* TODO: release firmware once rtl_phy_write_fw signals failures. */
	if (!IS_ERR_OR_NULL(rtl_fw))
		rtl_phy_write_fw(tp, rtl_fw);
}