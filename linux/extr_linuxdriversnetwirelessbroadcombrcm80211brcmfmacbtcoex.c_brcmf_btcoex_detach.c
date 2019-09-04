#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct brcmf_cfg80211_info {TYPE_1__* btcoex; } ;
struct TYPE_4__ {int timer_on; int /*<<< orphan*/  work; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_btcoex_boost_wifi (TYPE_1__*,int) ; 
 int /*<<< orphan*/  brcmf_btcoex_restore_part1 (TYPE_1__*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void brcmf_btcoex_detach(struct brcmf_cfg80211_info *cfg)
{
	brcmf_dbg(TRACE, "enter\n");

	if (!cfg->btcoex)
		return;

	if (cfg->btcoex->timer_on) {
		cfg->btcoex->timer_on = false;
		del_timer_sync(&cfg->btcoex->timer);
	}

	cancel_work_sync(&cfg->btcoex->work);

	brcmf_btcoex_boost_wifi(cfg->btcoex, false);
	brcmf_btcoex_restore_part1(cfg->btcoex);

	kfree(cfg->btcoex);
	cfg->btcoex = NULL;
}