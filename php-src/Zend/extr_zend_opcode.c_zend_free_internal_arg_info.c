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
struct TYPE_5__ {int fn_flags; size_t num_args; TYPE_2__* arg_info; } ;
typedef  TYPE_1__ zend_internal_function ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_internal_arg_info ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 int ZEND_ACC_HAS_TYPE_HINTS ; 
 int ZEND_ACC_VARIADIC ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_type_release (int /*<<< orphan*/ ,int) ; 

void zend_free_internal_arg_info(zend_internal_function *function) {
	if ((function->fn_flags & (ZEND_ACC_HAS_RETURN_TYPE|ZEND_ACC_HAS_TYPE_HINTS)) &&
		function->arg_info) {

		uint32_t i;
		uint32_t num_args = function->num_args + 1;
		zend_internal_arg_info *arg_info = function->arg_info - 1;

		if (function->fn_flags & ZEND_ACC_VARIADIC) {
			num_args++;
		}
		for (i = 0 ; i < num_args; i++) {
			zend_type_release(arg_info[i].type, /* persistent */ 1);
		}
		free(arg_info);
	}
}