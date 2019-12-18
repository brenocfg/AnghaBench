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
struct xt_rateest_match_info {int flags; int mode; struct xt_rateest* est2; struct xt_rateest* est1; int /*<<< orphan*/  name2; int /*<<< orphan*/  name1; } ;
struct xt_rateest {int dummy; } ;
struct xt_mtchk_param {int /*<<< orphan*/  net; struct xt_rateest_match_info* matchinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int XT_RATEEST_MATCH_ABS ; 
 int XT_RATEEST_MATCH_BPS ; 
#define  XT_RATEEST_MATCH_EQ 130 
#define  XT_RATEEST_MATCH_GT 129 
#define  XT_RATEEST_MATCH_LT 128 
 int XT_RATEEST_MATCH_PPS ; 
 int XT_RATEEST_MATCH_REL ; 
 int hweight32 (int) ; 
 struct xt_rateest* xt_rateest_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_rateest_put (int /*<<< orphan*/ ,struct xt_rateest*) ; 

__attribute__((used)) static int xt_rateest_mt_checkentry(const struct xt_mtchk_param *par)
{
	struct xt_rateest_match_info *info = par->matchinfo;
	struct xt_rateest *est1, *est2;
	int ret = -EINVAL;

	if (hweight32(info->flags & (XT_RATEEST_MATCH_ABS |
				     XT_RATEEST_MATCH_REL)) != 1)
		goto err1;

	if (!(info->flags & (XT_RATEEST_MATCH_BPS | XT_RATEEST_MATCH_PPS)))
		goto err1;

	switch (info->mode) {
	case XT_RATEEST_MATCH_EQ:
	case XT_RATEEST_MATCH_LT:
	case XT_RATEEST_MATCH_GT:
		break;
	default:
		goto err1;
	}

	ret  = -ENOENT;
	est1 = xt_rateest_lookup(par->net, info->name1);
	if (!est1)
		goto err1;

	est2 = NULL;
	if (info->flags & XT_RATEEST_MATCH_REL) {
		est2 = xt_rateest_lookup(par->net, info->name2);
		if (!est2)
			goto err2;
	}

	info->est1 = est1;
	info->est2 = est2;
	return 0;

err2:
	xt_rateest_put(par->net, est1);
err1:
	return ret;
}