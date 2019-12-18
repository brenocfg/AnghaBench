#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char underflow; char overflow; void* max; void* min; } ;
struct TYPE_8__ {int min_var; int max_var; int min_ssa_var; int max_ssa_var; int /*<<< orphan*/  negative; TYPE_2__ range; } ;
typedef  TYPE_3__ zend_ssa_range_constraint ;
struct TYPE_6__ {TYPE_3__ range; } ;
struct TYPE_9__ {int has_range_constraint; TYPE_1__ constraint; } ;
typedef  TYPE_4__ zend_ssa_phi ;
typedef  void* zend_long ;

/* Variables and functions */
 int /*<<< orphan*/  NEG_INIT ; 
 int /*<<< orphan*/  NEG_NONE ; 

__attribute__((used)) static void pi_range(
		zend_ssa_phi *phi, int min_var, int max_var, zend_long min, zend_long max,
		char underflow, char overflow, char negative) /* {{{ */
{
	zend_ssa_range_constraint *constraint = &phi->constraint.range;
	constraint->min_var = min_var;
	constraint->max_var = max_var;
	constraint->min_ssa_var = -1;
	constraint->max_ssa_var = -1;
	constraint->range.min = min;
	constraint->range.max = max;
	constraint->range.underflow = underflow;
	constraint->range.overflow = overflow;
	constraint->negative = negative ? NEG_INIT : NEG_NONE;
	phi->has_range_constraint = 1;
}