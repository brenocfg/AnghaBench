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
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int wlcore_cmd_send_failsafe (struct wl1271*,int /*<<< orphan*/ ,void*,size_t,size_t,int /*<<< orphan*/ ) ; 

int wl1271_cmd_send(struct wl1271 *wl, u16 id, void *buf, size_t len,
		    size_t res_len)
{
	int ret = wlcore_cmd_send_failsafe(wl, id, buf, len, res_len, 0);

	if (ret < 0)
		return ret;
	return 0;
}