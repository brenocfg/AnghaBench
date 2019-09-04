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
struct wl1251 {int dummy; } ;
struct acx_rts_threshold {int /*<<< orphan*/  threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DOT11_RTS_THRESHOLD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_rts_threshold*) ; 
 struct acx_rts_threshold* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_rts_threshold*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_rts_threshold(struct wl1251 *wl, u16 rts_threshold)
{
	struct acx_rts_threshold *rts;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx rts threshold");

	rts = kzalloc(sizeof(*rts), GFP_KERNEL);
	if (!rts)
		return -ENOMEM;

	rts->threshold = rts_threshold;

	ret = wl1251_cmd_configure(wl, DOT11_RTS_THRESHOLD, rts, sizeof(*rts));
	if (ret < 0) {
		wl1251_warning("failed to set rts threshold: %d", ret);
		goto out;
	}

out:
	kfree(rts);
	return ret;
}