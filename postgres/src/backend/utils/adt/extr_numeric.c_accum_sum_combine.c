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
typedef  int /*<<< orphan*/  NumericVar ;
typedef  int /*<<< orphan*/  NumericSumAccum ;

/* Variables and functions */
 int /*<<< orphan*/  accum_sum_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accum_sum_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
accum_sum_combine(NumericSumAccum *accum, NumericSumAccum *accum2)
{
	NumericVar	tmp_var;

	init_var(&tmp_var);

	accum_sum_final(accum2, &tmp_var);
	accum_sum_add(accum, &tmp_var);

	free_var(&tmp_var);
}