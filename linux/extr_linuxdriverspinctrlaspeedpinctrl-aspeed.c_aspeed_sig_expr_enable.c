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
struct aspeed_sig_expr {int dummy; } ;

/* Variables and functions */
 int aspeed_sig_expr_eval (struct aspeed_sig_expr const*,int,struct regmap* const*) ; 
 int aspeed_sig_expr_set (struct aspeed_sig_expr const*,int,struct regmap* const*) ; 

__attribute__((used)) static int aspeed_sig_expr_enable(const struct aspeed_sig_expr *expr,
				   struct regmap * const *maps)
{
	int ret;

	ret = aspeed_sig_expr_eval(expr, true, maps);
	if (ret < 0)
		return ret;

	if (!ret)
		return aspeed_sig_expr_set(expr, true, maps);

	return 0;
}