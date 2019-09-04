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
struct wl1251 {int dummy; } ;
struct acx_revision {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_FW_REV ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_revision*) ; 
 struct acx_revision* kzalloc (int,int /*<<< orphan*/ ) ; 
 int min (size_t,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int wl1251_cmd_interrogate (struct wl1251*,int /*<<< orphan*/ ,struct acx_revision*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*) ; 

int wl1251_acx_fw_version(struct wl1251 *wl, char *buf, size_t len)
{
	struct acx_revision *rev;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx fw rev");

	rev = kzalloc(sizeof(*rev), GFP_KERNEL);
	if (!rev)
		return -ENOMEM;

	ret = wl1251_cmd_interrogate(wl, ACX_FW_REV, rev, sizeof(*rev));
	if (ret < 0) {
		wl1251_warning("ACX_FW_REV interrogate failed");
		goto out;
	}

	/* be careful with the buffer sizes */
	strncpy(buf, rev->fw_version, min(len, sizeof(rev->fw_version)));

	/*
	 * if the firmware version string is exactly
	 * sizeof(rev->fw_version) long or fw_len is less than
	 * sizeof(rev->fw_version) it won't be null terminated
	 */
	buf[min(len, sizeof(rev->fw_version)) - 1] = '\0';

out:
	kfree(rev);
	return ret;
}