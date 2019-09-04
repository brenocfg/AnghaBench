#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ handler; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ internal_function; } ;
typedef  TYPE_2__ zend_function ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_FN (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_INTERNAL_FUNCTION ; 
 int /*<<< orphan*/  display_disabled_function ; 
 int /*<<< orphan*/  function_table ; 
 scalar_t__ zend_hash_str_find_ptr (int /*<<< orphan*/ ,char const*,size_t) ; 

int zend_optimizer_is_disabled_func(const char *name, size_t len) {
	zend_function *fbc = (zend_function *)zend_hash_str_find_ptr(EG(function_table), name, len);

	return (fbc && fbc->type == ZEND_INTERNAL_FUNCTION &&
			fbc->internal_function.handler == ZEND_FN(display_disabled_function));
}