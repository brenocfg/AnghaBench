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
struct acx_aid {int /*<<< orphan*/  aid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_AID ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_aid*) ; 
 struct acx_aid* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_aid*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_aid(struct wl1251 *wl, u16 aid)
{
	struct acx_aid *acx_aid;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx aid");

	acx_aid = kzalloc(sizeof(*acx_aid), GFP_KERNEL);
	if (!acx_aid)
		return -ENOMEM;

	acx_aid->aid = aid;

	ret = wl1251_cmd_configure(wl, ACX_AID, acx_aid, sizeof(*acx_aid));
	if (ret < 0) {
		wl1251_warning("failed to set aid: %d", ret);
		goto out;
	}

out:
	kfree(acx_aid);
	return ret;
}