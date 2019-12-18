#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct xt_rateest_match_info {int flags; int mode; scalar_t__ pps2; scalar_t__ bps2; TYPE_2__* est2; scalar_t__ pps1; scalar_t__ bps1; TYPE_1__* est1; } ;
struct xt_action_param {struct xt_rateest_match_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct gnet_stats_rate_est64 {scalar_t__ pps; scalar_t__ bps; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  rate_est; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate_est; } ;

/* Variables and functions */
 int XT_RATEEST_MATCH_ABS ; 
 int XT_RATEEST_MATCH_BPS ; 
 int XT_RATEEST_MATCH_DELTA ; 
#define  XT_RATEEST_MATCH_EQ 130 
#define  XT_RATEEST_MATCH_GT 129 
 int XT_RATEEST_MATCH_INVERT ; 
#define  XT_RATEEST_MATCH_LT 128 
 int XT_RATEEST_MATCH_PPS ; 
 int /*<<< orphan*/  gen_estimator_read (int /*<<< orphan*/ *,struct gnet_stats_rate_est64*) ; 

__attribute__((used)) static bool
xt_rateest_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_rateest_match_info *info = par->matchinfo;
	struct gnet_stats_rate_est64 sample = {0};
	u_int32_t bps1, bps2, pps1, pps2;
	bool ret = true;

	gen_estimator_read(&info->est1->rate_est, &sample);

	if (info->flags & XT_RATEEST_MATCH_DELTA) {
		bps1 = info->bps1 >= sample.bps ? info->bps1 - sample.bps : 0;
		pps1 = info->pps1 >= sample.pps ? info->pps1 - sample.pps : 0;
	} else {
		bps1 = sample.bps;
		pps1 = sample.pps;
	}

	if (info->flags & XT_RATEEST_MATCH_ABS) {
		bps2 = info->bps2;
		pps2 = info->pps2;
	} else {
		gen_estimator_read(&info->est2->rate_est, &sample);

		if (info->flags & XT_RATEEST_MATCH_DELTA) {
			bps2 = info->bps2 >= sample.bps ? info->bps2 - sample.bps : 0;
			pps2 = info->pps2 >= sample.pps ? info->pps2 - sample.pps : 0;
		} else {
			bps2 = sample.bps;
			pps2 = sample.pps;
		}
	}

	switch (info->mode) {
	case XT_RATEEST_MATCH_LT:
		if (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 < bps2;
		if (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 < pps2;
		break;
	case XT_RATEEST_MATCH_GT:
		if (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 > bps2;
		if (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 > pps2;
		break;
	case XT_RATEEST_MATCH_EQ:
		if (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 == bps2;
		if (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 == pps2;
		break;
	}

	ret ^= info->flags & XT_RATEEST_MATCH_INVERT ? true : false;
	return ret;
}