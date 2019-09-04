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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct brcms_phy {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */

__attribute__((used)) static s8
wlc_user_txpwr_antport_to_rfport(struct brcms_phy *pi, uint chan, u32 band,
				 u8 rate)
{
	return 0;
}