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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct wilc {int /*<<< orphan*/  rxq_cs; TYPE_1__ rxq_head; scalar_t__ quit; } ;
struct rxq_entry_t {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wilc_wlan_rxq_add(struct wilc *wilc, struct rxq_entry_t *rqe)
{
	if (wilc->quit)
		return;

	mutex_lock(&wilc->rxq_cs);
	list_add_tail(&rqe->list, &wilc->rxq_head.list);
	mutex_unlock(&wilc->rxq_cs);
}