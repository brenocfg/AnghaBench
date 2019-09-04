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

/* Variables and functions */
 int EINVAL ; 
 int MAXQUOTAS ; 
 int /*<<< orphan*/  Q_SYNC ; 
 int /*<<< orphan*/  iterate_supers (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  quota_sync_one ; 
 int security_quotactl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int quota_sync_all(int type)
{
	int ret;

	if (type >= MAXQUOTAS)
		return -EINVAL;
	ret = security_quotactl(Q_SYNC, type, 0, NULL);
	if (!ret)
		iterate_supers(quota_sync_one, &type);
	return ret;
}