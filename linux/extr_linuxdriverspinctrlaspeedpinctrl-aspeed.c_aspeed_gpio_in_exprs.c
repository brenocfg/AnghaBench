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
struct aspeed_sig_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ aspeed_expr_is_gpio (struct aspeed_sig_expr const*) ; 

__attribute__((used)) static bool aspeed_gpio_in_exprs(const struct aspeed_sig_expr **exprs)
{
	if (!exprs)
		return false;

	while (*exprs) {
		if (aspeed_expr_is_gpio(*exprs))
			return true;
		exprs++;
	}

	return false;
}