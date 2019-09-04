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
typedef  int /*<<< orphan*/  u8 ;
struct wl1251 {int dummy; } ;
struct acx_sleep_auth {int /*<<< orphan*/  sleep_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_SLEEP_AUTH ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_sleep_auth*) ; 
 struct acx_sleep_auth* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_sleep_auth*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 

int wl1251_acx_sleep_auth(struct wl1251 *wl, u8 sleep_auth)
{
	struct acx_sleep_auth *auth;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx sleep auth");

	auth = kzalloc(sizeof(*auth), GFP_KERNEL);
	if (!auth)
		return -ENOMEM;

	auth->sleep_auth = sleep_auth;

	ret = wl1251_cmd_configure(wl, ACX_SLEEP_AUTH, auth, sizeof(*auth));

	kfree(auth);
	return ret;
}