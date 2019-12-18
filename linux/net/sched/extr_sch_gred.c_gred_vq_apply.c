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
typedef  size_t u32 ;
struct nlattr {int dummy; } ;
struct gred_sched {TYPE_1__** tab; } ;
struct TYPE_2__ {void* red_flags; } ;

/* Variables and functions */
 size_t TCA_GRED_VQ_DP ; 
 size_t TCA_GRED_VQ_FLAGS ; 
 int /*<<< orphan*/  TCA_GRED_VQ_MAX ; 
 int /*<<< orphan*/  gred_vq_policy ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gred_vq_apply(struct gred_sched *table, const struct nlattr *entry)
{
	struct nlattr *tb[TCA_GRED_VQ_MAX + 1];
	u32 dp;

	nla_parse_nested_deprecated(tb, TCA_GRED_VQ_MAX, entry,
				    gred_vq_policy, NULL);

	dp = nla_get_u32(tb[TCA_GRED_VQ_DP]);

	if (tb[TCA_GRED_VQ_FLAGS])
		table->tab[dp]->red_flags = nla_get_u32(tb[TCA_GRED_VQ_FLAGS]);
}