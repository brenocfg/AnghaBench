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
typedef  int uint32_t ;
struct hostapd_data {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int __BSS_MGMT_EN_MAX ; 
 int __hostapd_bss_mgmt_enable_f (struct hostapd_data*,int) ; 
 int /*<<< orphan*/  ieee802_11_update_beacons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__hostapd_bss_mgmt_enable(struct hostapd_data *hapd, uint32_t flags)
{
	bool update = false;
	int i;

	for (i = 0; i < __BSS_MGMT_EN_MAX; i++) {
		if (!(flags & (1 << i)))
			continue;

		update |= __hostapd_bss_mgmt_enable_f(hapd, i);
	}

	if (update)
		ieee802_11_update_beacons(hapd->iface);
}