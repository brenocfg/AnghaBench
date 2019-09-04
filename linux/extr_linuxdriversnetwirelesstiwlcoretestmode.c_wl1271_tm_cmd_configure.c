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
struct wl1271_command {int dummy; } ;
struct wl1271 {int /*<<< orphan*/  mutex; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TESTMODE ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 size_t WL1271_TM_ATTR_DATA ; 
 size_t WL1271_TM_ATTR_IE_ID ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

__attribute__((used)) static int wl1271_tm_cmd_configure(struct wl1271 *wl, struct nlattr *tb[])
{
	int buf_len, ret;
	void *buf;
	u8 ie_id;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd configure");

	if (!tb[WL1271_TM_ATTR_DATA])
		return -EINVAL;
	if (!tb[WL1271_TM_ATTR_IE_ID])
		return -EINVAL;

	ie_id = nla_get_u8(tb[WL1271_TM_ATTR_IE_ID]);
	buf = nla_data(tb[WL1271_TM_ATTR_DATA]);
	buf_len = nla_len(tb[WL1271_TM_ATTR_DATA]);

	if (buf_len > sizeof(struct wl1271_command))
		return -EMSGSIZE;

	mutex_lock(&wl->mutex);
	ret = wl1271_cmd_configure(wl, ie_id, buf, buf_len);
	mutex_unlock(&wl->mutex);

	if (ret < 0) {
		wl1271_warning("testmode cmd configure failed: %d", ret);
		return ret;
	}

	return 0;
}