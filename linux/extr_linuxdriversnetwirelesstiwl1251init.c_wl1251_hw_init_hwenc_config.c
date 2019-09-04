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
struct wl1251 {int /*<<< orphan*/  default_key; } ;

/* Variables and functions */
 int wl1251_acx_default_key (struct wl1251*,int /*<<< orphan*/ ) ; 
 int wl1251_acx_feature_cfg (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_warning (char*) ; 

int wl1251_hw_init_hwenc_config(struct wl1251 *wl)
{
	int ret;

	ret = wl1251_acx_feature_cfg(wl, 0);
	if (ret < 0) {
		wl1251_warning("couldn't set feature config");
		return ret;
	}

	ret = wl1251_acx_default_key(wl, wl->default_key);
	if (ret < 0) {
		wl1251_warning("couldn't set default key");
		return ret;
	}

	return 0;
}