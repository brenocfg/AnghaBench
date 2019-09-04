#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ underflow; scalar_t__ min; scalar_t__ overflow; scalar_t__ max; } ;
struct TYPE_5__ {int has_range; TYPE_2__ range; } ;
typedef  TYPE_1__ zend_ssa_var_info ;
typedef  TYPE_2__ zend_ssa_range ;

/* Variables and functions */
 scalar_t__ ZEND_LONG_MAX ; 
 scalar_t__ ZEND_LONG_MIN ; 

int zend_inference_narrowing_meet(zend_ssa_var_info *var_info, zend_ssa_range *r)
{
	if (!var_info->has_range) {
		var_info->has_range = 1;
	} else {
		if (!r->underflow &&
		    !var_info->range.underflow &&
		    var_info->range.min < r->min) {
			r->min = var_info->range.min;
		}
		if (!r->overflow &&
		    !var_info->range.overflow &&
		    var_info->range.max > r->max) {
			r->max = var_info->range.max;
		}
		if (r->underflow) {
			r->min = ZEND_LONG_MIN;
		}
		if (r->overflow) {
			r->max = ZEND_LONG_MAX;
		}
		if (var_info->range.min == r->min &&
		    var_info->range.max == r->max &&
		    var_info->range.underflow == r->underflow &&
		    var_info->range.overflow == r->overflow) {
			return 0;
		}
	}
	var_info->range = *r;
	return 1;
}