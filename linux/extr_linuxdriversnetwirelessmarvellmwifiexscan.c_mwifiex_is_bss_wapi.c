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
struct TYPE_2__ {scalar_t__ wapi_enabled; } ;
struct mwifiex_private {TYPE_1__ sec_info; } ;
struct mwifiex_bssdescriptor {int /*<<< orphan*/  bcn_wapi_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_BSS_AC_ACCESS_DELAY ; 
 scalar_t__ has_ieee_hdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mwifiex_is_bss_wapi(struct mwifiex_private *priv,
		    struct mwifiex_bssdescriptor *bss_desc)
{
	if (priv->sec_info.wapi_enabled &&
	    has_ieee_hdr(bss_desc->bcn_wapi_ie, WLAN_EID_BSS_AC_ACCESS_DELAY))
		return true;
	return false;
}