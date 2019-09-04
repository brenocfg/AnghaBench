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
struct TYPE_2__ {int /*<<< orphan*/  fw_stats_len; } ;
struct wl1271 {TYPE_1__ stats; } ;
struct acx_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_STATISTICS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int wl1271_cmd_interrogate (struct wl1271*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_statistics(struct wl1271 *wl, void *stats)
{
	int ret;

	wl1271_debug(DEBUG_ACX, "acx statistics");

	ret = wl1271_cmd_interrogate(wl, ACX_STATISTICS, stats,
				     sizeof(struct acx_header),
				     wl->stats.fw_stats_len);
	if (ret < 0) {
		wl1271_warning("acx statistics failed: %d", ret);
		return -ENOMEM;
	}

	return 0;
}