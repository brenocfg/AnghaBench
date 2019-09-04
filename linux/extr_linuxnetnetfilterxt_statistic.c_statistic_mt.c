#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int every; } ;
struct TYPE_5__ {int probability; } ;
struct TYPE_8__ {TYPE_3__ nth; TYPE_1__ random; } ;
struct xt_statistic_info {int flags; int mode; TYPE_4__ u; TYPE_2__* master; } ;
struct xt_action_param {struct xt_statistic_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int XT_STATISTIC_INVERT ; 
#define  XT_STATISTIC_MODE_NTH 129 
#define  XT_STATISTIC_MODE_RANDOM 128 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int prandom_u32 () ; 

__attribute__((used)) static bool
statistic_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_statistic_info *info = par->matchinfo;
	bool ret = info->flags & XT_STATISTIC_INVERT;
	int nval, oval;

	switch (info->mode) {
	case XT_STATISTIC_MODE_RANDOM:
		if ((prandom_u32() & 0x7FFFFFFF) < info->u.random.probability)
			ret = !ret;
		break;
	case XT_STATISTIC_MODE_NTH:
		do {
			oval = atomic_read(&info->master->count);
			nval = (oval == info->u.nth.every) ? 0 : oval + 1;
		} while (atomic_cmpxchg(&info->master->count, oval, nval) != oval);
		if (nval == 0)
			ret = !ret;
		break;
	}

	return ret;
}