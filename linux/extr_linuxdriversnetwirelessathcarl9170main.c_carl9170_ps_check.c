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
struct ar9170 {int /*<<< orphan*/  ps_work; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void carl9170_ps_check(struct ar9170 *ar)
{
	ieee80211_queue_work(ar->hw, &ar->ps_work);
}