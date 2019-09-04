#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_5__ {TYPE_1__ nth; } ;
struct xt_statistic_info {scalar_t__ mode; int flags; TYPE_2__ u; TYPE_3__* master; } ;
struct xt_mtchk_param {struct xt_statistic_info* matchinfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int XT_STATISTIC_MASK ; 
 scalar_t__ XT_STATISTIC_MODE_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int statistic_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_statistic_info *info = par->matchinfo;

	if (info->mode > XT_STATISTIC_MODE_MAX ||
	    info->flags & ~XT_STATISTIC_MASK)
		return -EINVAL;

	info->master = kzalloc(sizeof(*info->master), GFP_KERNEL);
	if (info->master == NULL)
		return -ENOMEM;
	atomic_set(&info->master->count, info->u.nth.count);

	return 0;
}