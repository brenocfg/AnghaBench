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
typedef  int /*<<< orphan*/  u32 ;
struct wl1271_acx_host_config_bitmap {int /*<<< orphan*/  host_cfg_bitmap; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_HOST_IF_CFG_BITMAP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_host_config_bitmap*) ; 
 struct wl1271_acx_host_config_bitmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_host_config_bitmap*,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_host_if_cfg_bitmap(struct wl1271 *wl, u32 host_cfg_bitmap)
{
	struct wl1271_acx_host_config_bitmap *bitmap_conf;
	int ret;

	bitmap_conf = kzalloc(sizeof(*bitmap_conf), GFP_KERNEL);
	if (!bitmap_conf) {
		ret = -ENOMEM;
		goto out;
	}

	bitmap_conf->host_cfg_bitmap = cpu_to_le32(host_cfg_bitmap);

	ret = wl1271_cmd_configure(wl, ACX_HOST_IF_CFG_BITMAP,
				   bitmap_conf, sizeof(*bitmap_conf));
	if (ret < 0) {
		wl1271_warning("wl1271 bitmap config opt failed: %d", ret);
		goto out;
	}

out:
	kfree(bitmap_conf);

	return ret;
}