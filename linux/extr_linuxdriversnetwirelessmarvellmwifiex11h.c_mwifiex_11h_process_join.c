#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int is_11h_active; } ;
struct mwifiex_private {TYPE_1__ state_11h; } ;
struct mwifiex_bssdescriptor {int /*<<< orphan*/  cap_info_bitmap; scalar_t__ sensed_11h; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_CAPABILITY_SPECTRUM_MGMT ; 
 int /*<<< orphan*/  mwifiex_11h_activate (struct mwifiex_private*,int) ; 
 int /*<<< orphan*/  mwifiex_11h_process_infra_join (struct mwifiex_private*,int /*<<< orphan*/ **,struct mwifiex_bssdescriptor*) ; 

void mwifiex_11h_process_join(struct mwifiex_private *priv, u8 **buffer,
			      struct mwifiex_bssdescriptor *bss_desc)
{
	if (bss_desc->sensed_11h) {
		/* Activate 11h functions in firmware, turns on capability
		 * bit
		 */
		mwifiex_11h_activate(priv, true);
		priv->state_11h.is_11h_active = true;
		bss_desc->cap_info_bitmap |= WLAN_CAPABILITY_SPECTRUM_MGMT;
		mwifiex_11h_process_infra_join(priv, buffer, bss_desc);
	} else {
		/* Deactivate 11h functions in the firmware */
		mwifiex_11h_activate(priv, false);
		priv->state_11h.is_11h_active = false;
		bss_desc->cap_info_bitmap &= ~WLAN_CAPABILITY_SPECTRUM_MGMT;
	}
}