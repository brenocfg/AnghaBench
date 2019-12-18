#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ dscale; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 int /*<<< orphan*/  add_var (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cmp_var (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  const_one ; 
 int /*<<< orphan*/  div_var (TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  floor_var (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  free_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mul_var (TYPE_1__*,TYPE_1__ const*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  select_div_scale (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sub_var (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void
compute_bucket(Numeric operand, Numeric bound1, Numeric bound2,
			   const NumericVar *count_var, NumericVar *result_var)
{
	NumericVar	bound1_var;
	NumericVar	bound2_var;
	NumericVar	operand_var;

	init_var_from_num(bound1, &bound1_var);
	init_var_from_num(bound2, &bound2_var);
	init_var_from_num(operand, &operand_var);

	if (cmp_var(&bound1_var, &bound2_var) < 0)
	{
		sub_var(&operand_var, &bound1_var, &operand_var);
		sub_var(&bound2_var, &bound1_var, &bound2_var);
		div_var(&operand_var, &bound2_var, result_var,
				select_div_scale(&operand_var, &bound2_var), true);
	}
	else
	{
		sub_var(&bound1_var, &operand_var, &operand_var);
		sub_var(&bound1_var, &bound2_var, &bound1_var);
		div_var(&operand_var, &bound1_var, result_var,
				select_div_scale(&operand_var, &bound1_var), true);
	}

	mul_var(result_var, count_var, result_var,
			result_var->dscale + count_var->dscale);
	add_var(result_var, &const_one, result_var);
	floor_var(result_var, result_var);

	free_var(&bound1_var);
	free_var(&bound2_var);
	free_var(&operand_var);
}