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
struct wl1271 {void* sleep_auth; } ;
struct acx_sleep_auth {void* sleep_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_SLEEP_AUTH ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_sleep_auth*) ; 
 struct acx_sleep_auth* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_sleep_auth*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  wl1271_error (char*,void*,int) ; 

int wl1271_acx_sleep_auth(struct wl1271 *wl, u8 sleep_auth)
{
	struct acx_sleep_auth *auth;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx sleep auth %d", sleep_auth);

	auth = kzalloc(sizeof(*auth), GFP_KERNEL);
	if (!auth) {
		ret = -ENOMEM;
		goto out;
	}

	auth->sleep_auth = sleep_auth;

	ret = wl1271_cmd_configure(wl, ACX_SLEEP_AUTH, auth, sizeof(*auth));
	if (ret < 0) {
		wl1271_error("could not configure sleep_auth to %d: %d",
			     sleep_auth, ret);
		goto out;
	}

	wl->sleep_auth = sleep_auth;
out:
	kfree(auth);
	return ret;
}