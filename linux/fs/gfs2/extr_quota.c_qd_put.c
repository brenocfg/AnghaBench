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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ count; } ;
struct gfs2_quota_data {TYPE_1__ qd_lockref; int /*<<< orphan*/  qd_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_qd_lru ; 
 int /*<<< orphan*/  list_lru_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lockref_put_or_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qd_put(struct gfs2_quota_data *qd)
{
	if (lockref_put_or_lock(&qd->qd_lockref))
		return;

	qd->qd_lockref.count = 0;
	list_lru_add(&gfs2_qd_lru, &qd->qd_lru);
	spin_unlock(&qd->qd_lockref.lock);

}