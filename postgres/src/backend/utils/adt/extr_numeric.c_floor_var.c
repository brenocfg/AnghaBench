#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ sign; } ;
typedef  TYPE_1__ const NumericVar ;

/* Variables and functions */
 scalar_t__ NUMERIC_NEG ; 
 scalar_t__ cmp_var (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  const_one ; 
 int /*<<< orphan*/  free_var (TYPE_1__ const*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__ const*) ; 
 int /*<<< orphan*/  set_var_from_var (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  sub_var (TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  trunc_var (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
floor_var(const NumericVar *var, NumericVar *result)
{
	NumericVar	tmp;

	init_var(&tmp);
	set_var_from_var(var, &tmp);

	trunc_var(&tmp, 0);

	if (var->sign == NUMERIC_NEG && cmp_var(var, &tmp) != 0)
		sub_var(&tmp, &const_one, &tmp);

	set_var_from_var(&tmp, result);
	free_var(&tmp);
}