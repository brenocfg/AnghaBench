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
typedef  int /*<<< orphan*/  uint32_t ;
struct wusbhc {int /*<<< orphan*/  mutex; scalar_t__ active; } ;
struct whc {scalar_t__ base; int /*<<< orphan*/  periodic_list_wq; struct wusbhc wusbhc; } ;

/* Variables and functions */
 scalar_t__ WUSBCMD ; 
 int WUSBCMD_PERIODIC_UPDATED ; 
 int le_readl (scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whc_hw_error (struct whc*,char*) ; 
 int /*<<< orphan*/  whc_write_wusbcmd (struct whc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pzl_update(struct whc *whc, uint32_t wusbcmd)
{
	struct wusbhc *wusbhc = &whc->wusbhc;
	long t;

	mutex_lock(&wusbhc->mutex);
	if (wusbhc->active) {
		whc_write_wusbcmd(whc, wusbcmd, wusbcmd);
		t = wait_event_timeout(
			whc->periodic_list_wq,
			(le_readl(whc->base + WUSBCMD) & WUSBCMD_PERIODIC_UPDATED) == 0,
			msecs_to_jiffies(1000));
		if (t == 0)
			whc_hw_error(whc, "PZL update timeout");
	}
	mutex_unlock(&wusbhc->mutex);
}