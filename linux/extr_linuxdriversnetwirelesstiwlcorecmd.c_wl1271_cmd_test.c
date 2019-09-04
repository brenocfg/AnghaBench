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
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEST ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,void*,size_t,size_t) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

int wl1271_cmd_test(struct wl1271 *wl, void *buf, size_t buf_len, u8 answer)
{
	int ret;
	size_t res_len = 0;

	wl1271_debug(DEBUG_CMD, "cmd test");

	if (answer)
		res_len = buf_len;

	ret = wl1271_cmd_send(wl, CMD_TEST, buf, buf_len, res_len);

	if (ret < 0) {
		wl1271_warning("TEST command failed");
		return ret;
	}

	return ret;
}