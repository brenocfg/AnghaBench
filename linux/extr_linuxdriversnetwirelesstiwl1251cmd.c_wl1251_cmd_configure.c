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
struct acx_header {size_t len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONFIGURE ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int wl1251_cmd_send (struct wl1251*,int /*<<< orphan*/ ,struct acx_header*,size_t) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*) ; 

int wl1251_cmd_configure(struct wl1251 *wl, u16 id, void *buf, size_t len)
{
	struct acx_header *acx = buf;
	int ret;

	wl1251_debug(DEBUG_CMD, "cmd configure");

	acx->id = id;

	/* payload length, does not include any headers */
	acx->len = len - sizeof(*acx);

	ret = wl1251_cmd_send(wl, CMD_CONFIGURE, acx, len);
	if (ret < 0) {
		wl1251_warning("CONFIGURE command NOK");
		return ret;
	}

	return 0;
}