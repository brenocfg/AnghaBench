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
struct wl1251 {void* default_key; } ;
struct acx_dot11_default_key {void* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DOT11_DEFAULT_KEY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_dot11_default_key*) ; 
 struct acx_dot11_default_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_dot11_default_key*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 

int wl1251_acx_default_key(struct wl1251 *wl, u8 key_id)
{
	struct acx_dot11_default_key *default_key;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx dot11_default_key (%d)", key_id);

	default_key = kzalloc(sizeof(*default_key), GFP_KERNEL);
	if (!default_key)
		return -ENOMEM;

	default_key->id = key_id;

	ret = wl1251_cmd_configure(wl, DOT11_DEFAULT_KEY,
				   default_key, sizeof(*default_key));
	if (ret < 0) {
		wl1251_error("Couldn't set default key");
		goto out;
	}

	wl->default_key = key_id;

out:
	kfree(default_key);
	return ret;
}