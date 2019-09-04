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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */

s8 wlc_phy_upd_rssi_offset(struct brcms_phy *pi, s8 rssi, u16 chanspec)
{

	return rssi;
}