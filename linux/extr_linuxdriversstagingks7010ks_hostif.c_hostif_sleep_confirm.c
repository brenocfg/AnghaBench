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
struct TYPE_2__ {int /*<<< orphan*/  doze_request; } ;
struct ks_wlan_private {int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; TYPE_1__ sleepstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
void hostif_sleep_confirm(struct ks_wlan_private *priv)
{
	atomic_set(&priv->sleepstatus.doze_request, 1);
	queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
}