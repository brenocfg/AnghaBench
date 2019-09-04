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
typedef  void* u8 ;
struct wl1251 {int dummy; } ;
struct acx_low_rssi {int type; void* depth; void* weight; int /*<<< orphan*/  threshold; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  enum wl1251_acx_low_rssi_type { ____Placeholder_wl1251_acx_low_rssi_type } wl1251_acx_low_rssi_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_LOW_RSSI ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_low_rssi*) ; 
 struct acx_low_rssi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_low_rssi*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_low_rssi(struct wl1251 *wl, s8 threshold, u8 weight,
			u8 depth, enum wl1251_acx_low_rssi_type type)
{
	struct acx_low_rssi *rssi;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx low rssi");

	rssi = kzalloc(sizeof(*rssi), GFP_KERNEL);
	if (!rssi)
		return -ENOMEM;

	rssi->threshold = threshold;
	rssi->weight = weight;
	rssi->depth = depth;
	rssi->type = type;

	ret = wl1251_cmd_configure(wl, ACX_LOW_RSSI, rssi, sizeof(*rssi));
	if (ret < 0)
		wl1251_warning("failed to set low rssi threshold: %d", ret);

	kfree(rssi);
	return ret;
}