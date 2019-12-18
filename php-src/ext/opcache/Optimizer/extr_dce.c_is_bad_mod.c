#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* var_info; } ;
typedef  TYPE_2__ zend_ssa ;
typedef  int zend_bool ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 int MAY_BE_REF ; 

__attribute__((used)) static inline zend_bool is_bad_mod(const zend_ssa *ssa, int use, int def) {
	if (def < 0) {
		/* This modification is not tracked by SSA, assume the worst */
		return 1;
	}
	if (ssa->var_info[use].type & MAY_BE_REF) {
		/* Modification of reference may have side-effect */
		return 1;
	}
	return 0;
}