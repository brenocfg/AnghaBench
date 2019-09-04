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
typedef  scalar_t__ u8 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_acx_arp_filter {int /*<<< orphan*/  address; scalar_t__ enable; int /*<<< orphan*/  version; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_ARP_IP_FILTER ; 
 int /*<<< orphan*/  ACX_IPV4_ADDR_SIZE ; 
 int /*<<< orphan*/  ACX_IPV4_VERSION ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_arp_filter*) ; 
 struct wl1271_acx_arp_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_arp_filter*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_arp_ip_filter(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			     u8 enable, __be32 address)
{
	struct wl1271_acx_arp_filter *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx arp ip filter, enable: %d", enable);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->role_id = wlvif->role_id;
	acx->version = ACX_IPV4_VERSION;
	acx->enable = enable;

	if (enable)
		memcpy(acx->address, &address, ACX_IPV4_ADDR_SIZE);

	ret = wl1271_cmd_configure(wl, ACX_ARP_IP_FILTER,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("failed to set arp ip filter: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}