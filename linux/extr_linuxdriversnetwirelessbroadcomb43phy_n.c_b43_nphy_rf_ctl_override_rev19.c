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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void b43_nphy_rf_ctl_override_rev19(struct b43_wldev *dev, u16 field,
					   u16 value, u8 core, bool off,
					   u8 override_id)
{
	/* TODO */
}