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
typedef  int /*<<< orphan*/  u8 ;
struct wl1271_link {int dummy; } ;
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* lnk_high_prio ) (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_link*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int stub1 (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_link*) ; 

__attribute__((used)) static inline bool
wlcore_hw_lnk_high_prio(struct wl1271 *wl, u8 hlid,
			struct wl1271_link *lnk)
{
	if (!wl->ops->lnk_high_prio)
		BUG_ON(1);

	return wl->ops->lnk_high_prio(wl, hlid, lnk);
}