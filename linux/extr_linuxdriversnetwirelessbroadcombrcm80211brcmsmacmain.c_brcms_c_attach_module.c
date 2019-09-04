#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct brcms_c_info {int /*<<< orphan*/  wiphy; int /*<<< orphan*/ * ampdu; int /*<<< orphan*/ * asi; TYPE_1__* pub; } ;
struct TYPE_2__ {int unit; } ;

/* Variables and functions */
 int /*<<< orphan*/ * brcms_c_ampdu_attach (struct brcms_c_info*) ; 
 int /*<<< orphan*/ * brcms_c_antsel_attach (struct brcms_c_info*) ; 
 scalar_t__ brcms_c_stf_attach (struct brcms_c_info*) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint brcms_c_attach_module(struct brcms_c_info *wlc)
{
	uint err = 0;
	uint unit;
	unit = wlc->pub->unit;

	wlc->asi = brcms_c_antsel_attach(wlc);
	if (wlc->asi == NULL) {
		wiphy_err(wlc->wiphy, "wl%d: attach: antsel_attach "
			  "failed\n", unit);
		err = 44;
		goto fail;
	}

	wlc->ampdu = brcms_c_ampdu_attach(wlc);
	if (wlc->ampdu == NULL) {
		wiphy_err(wlc->wiphy, "wl%d: attach: ampdu_attach "
			  "failed\n", unit);
		err = 50;
		goto fail;
	}

	if ((brcms_c_stf_attach(wlc) != 0)) {
		wiphy_err(wlc->wiphy, "wl%d: attach: stf_attach "
			  "failed\n", unit);
		err = 68;
		goto fail;
	}
 fail:
	return err;
}