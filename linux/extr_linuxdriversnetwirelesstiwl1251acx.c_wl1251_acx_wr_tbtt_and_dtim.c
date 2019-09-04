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
typedef  int /*<<< orphan*/  u16 ;
struct wl1251_acx_wr_tbtt_and_dtim {int /*<<< orphan*/  dtim; int /*<<< orphan*/  tbtt; } ;
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_WR_TBTT_AND_DTIM ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1251_acx_wr_tbtt_and_dtim*) ; 
 struct wl1251_acx_wr_tbtt_and_dtim* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct wl1251_acx_wr_tbtt_and_dtim*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_wr_tbtt_and_dtim(struct wl1251 *wl, u16 tbtt, u8 dtim)
{
	struct wl1251_acx_wr_tbtt_and_dtim *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx tbtt and dtim");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->tbtt = tbtt;
	acx->dtim = dtim;

	ret = wl1251_cmd_configure(wl, ACX_WR_TBTT_AND_DTIM,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("failed to set tbtt and dtim: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}