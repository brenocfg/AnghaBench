#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct brcms_info {TYPE_4__* pub; TYPE_3__* wlc; } ;
struct TYPE_8__ {int /*<<< orphan*/  ieee_hw; } ;
struct TYPE_7__ {TYPE_2__* pub; TYPE_1__* hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  unit; } ;
struct TYPE_5__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_reset (struct brcms_info*) ; 
 int /*<<< orphan*/  ieee80211_restart_hw (int /*<<< orphan*/ ) ; 

void brcms_fatal_error(struct brcms_info *wl)
{
	brcms_err(wl->wlc->hw->d11core, "wl%d: fatal error, reinitializing\n",
		  wl->wlc->pub->unit);
	brcms_reset(wl);
	ieee80211_restart_hw(wl->pub->ieee_hw);
}