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
struct aspeed_sig_expr {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct aspeed_sig_expr *aspeed_find_expr_by_name(
		const struct aspeed_sig_expr **exprs, const char *name)
{
	while (*exprs) {
		if (strcmp((*exprs)->function, name) == 0)
			return *exprs;
		exprs++;
	}

	return NULL;
}