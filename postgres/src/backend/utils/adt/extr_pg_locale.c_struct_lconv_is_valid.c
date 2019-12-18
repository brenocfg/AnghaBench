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
struct lconv {int /*<<< orphan*/ * negative_sign; int /*<<< orphan*/ * positive_sign; int /*<<< orphan*/ * mon_grouping; int /*<<< orphan*/ * mon_thousands_sep; int /*<<< orphan*/ * mon_decimal_point; int /*<<< orphan*/ * currency_symbol; int /*<<< orphan*/ * int_curr_symbol; int /*<<< orphan*/ * grouping; int /*<<< orphan*/ * thousands_sep; int /*<<< orphan*/ * decimal_point; } ;

/* Variables and functions */

__attribute__((used)) static bool
struct_lconv_is_valid(struct lconv *s)
{
	if (s->decimal_point == NULL)
		return false;
	if (s->thousands_sep == NULL)
		return false;
	if (s->grouping == NULL)
		return false;
	if (s->int_curr_symbol == NULL)
		return false;
	if (s->currency_symbol == NULL)
		return false;
	if (s->mon_decimal_point == NULL)
		return false;
	if (s->mon_thousands_sep == NULL)
		return false;
	if (s->mon_grouping == NULL)
		return false;
	if (s->positive_sign == NULL)
		return false;
	if (s->negative_sign == NULL)
		return false;
	return true;
}