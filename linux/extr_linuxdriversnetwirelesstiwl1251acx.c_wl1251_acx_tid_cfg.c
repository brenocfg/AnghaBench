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
struct wl1251_acx_tid_cfg {int type; int ps_scheme; int ack_policy; void* tsid; void* queue; } ;
struct wl1251 {int dummy; } ;
typedef  enum wl1251_acx_ps_scheme { ____Placeholder_wl1251_acx_ps_scheme } wl1251_acx_ps_scheme ;
typedef  enum wl1251_acx_channel_type { ____Placeholder_wl1251_acx_channel_type } wl1251_acx_channel_type ;
typedef  enum wl1251_acx_ack_policy { ____Placeholder_wl1251_acx_ack_policy } wl1251_acx_ack_policy ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_TID_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1251_acx_tid_cfg*) ; 
 struct wl1251_acx_tid_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_acx_tid_cfg*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,void*,int,void*,int,int) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_tid_cfg(struct wl1251 *wl, u8 queue,
		       enum wl1251_acx_channel_type type,
		       u8 tsid, enum wl1251_acx_ps_scheme ps_scheme,
		       enum wl1251_acx_ack_policy ack_policy)
{
	struct wl1251_acx_tid_cfg *acx;
	int ret = 0;

	wl1251_debug(DEBUG_ACX, "acx tid cfg %d type %d tsid %d "
		     "ps_scheme %d ack_policy %d", queue, type, tsid,
		     ps_scheme, ack_policy);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->queue = queue;
	acx->type = type;
	acx->tsid = tsid;
	acx->ps_scheme = ps_scheme;
	acx->ack_policy = ack_policy;

	ret = wl1251_cmd_configure(wl, ACX_TID_CFG, acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("acx tid cfg failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}