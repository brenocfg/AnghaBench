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
struct TYPE_2__ {int /*<<< orphan*/  wakeup_wait; int /*<<< orphan*/  snooze_guard; int /*<<< orphan*/  confirm_wait; int /*<<< orphan*/  status; } ;
struct ks_wlan_private {int /*<<< orphan*/  wakeup_work; TYPE_1__ psstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_NONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ks_wlan_hw_wakeup_task ; 

__attribute__((used)) static inline void hostif_power_save_init(struct ks_wlan_private *priv)
{
	atomic_set(&priv->psstatus.status, PS_NONE);
	atomic_set(&priv->psstatus.confirm_wait, 0);
	atomic_set(&priv->psstatus.snooze_guard, 0);
	init_completion(&priv->psstatus.wakeup_wait);
	INIT_WORK(&priv->wakeup_work, ks_wlan_hw_wakeup_task);
}