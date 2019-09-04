#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_uchar ;
typedef  int zend_bool ;
struct TYPE_3__ {int children; } ;
typedef  TYPE_1__ zend_ast_list ;

/* Variables and functions */
 int CG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_COMPILE_NO_JUMPTABLES ; 
 int /*<<< orphan*/  compiler_options ; 

__attribute__((used)) static zend_bool should_use_jumptable(zend_ast_list *cases, zend_uchar jumptable_type) {
	if (CG(compiler_options) & ZEND_COMPILE_NO_JUMPTABLES) {
		return 0;
	}

	/* Thresholds are chosen based on when the average switch time for equidistributed
	 * input becomes smaller when using the jumptable optimization. */
	if (jumptable_type == IS_LONG) {
		return cases->children >= 5;
	} else {
		ZEND_ASSERT(jumptable_type == IS_STRING);
		return cases->children >= 2;
	}
}