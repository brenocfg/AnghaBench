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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xfrm_policy {int dummy; } ;
struct xfrm_pol_inexact_candidates {int /*<<< orphan*/ * res; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct xfrm_policy*) ; 
 struct xfrm_policy* __xfrm_policy_eval_candidates (int /*<<< orphan*/ ,struct xfrm_policy*,struct flowi const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_policy *
xfrm_policy_eval_candidates(struct xfrm_pol_inexact_candidates *cand,
			    struct xfrm_policy *prefer,
			    const struct flowi *fl,
			    u8 type, u16 family, int dir, u32 if_id)
{
	struct xfrm_policy *tmp;
	int i;

	for (i = 0; i < ARRAY_SIZE(cand->res); i++) {
		tmp = __xfrm_policy_eval_candidates(cand->res[i],
						    prefer,
						    fl, type, family, dir,
						    if_id);
		if (!tmp)
			continue;

		if (IS_ERR(tmp))
			return tmp;
		prefer = tmp;
	}

	return prefer;
}