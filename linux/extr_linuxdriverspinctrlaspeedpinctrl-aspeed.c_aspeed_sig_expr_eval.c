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
struct regmap {int dummy; } ;
struct aspeed_sig_expr {int ndescs; struct aspeed_sig_desc* descs; } ;
struct aspeed_sig_desc {size_t ip; } ;

/* Variables and functions */
 int aspeed_sig_desc_eval (struct aspeed_sig_desc const*,int,struct regmap* const) ; 

__attribute__((used)) static int aspeed_sig_expr_eval(const struct aspeed_sig_expr *expr,
				 bool enabled, struct regmap * const *maps)
{
	int i;
	int ret;

	for (i = 0; i < expr->ndescs; i++) {
		const struct aspeed_sig_desc *desc = &expr->descs[i];

		ret = aspeed_sig_desc_eval(desc, enabled, maps[desc->ip]);
		if (ret <= 0)
			return ret;
	}

	return 1;
}