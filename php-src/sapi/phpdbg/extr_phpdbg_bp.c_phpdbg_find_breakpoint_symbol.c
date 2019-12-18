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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {scalar_t__ function_name; scalar_t__ scope; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_2__ zend_function ;
typedef  int /*<<< orphan*/  phpdbg_breakbase_t ;

/* Variables and functions */
 size_t PHPDBG_BREAK_SYM ; 
 int /*<<< orphan*/ * PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 int /*<<< orphan*/  bp ; 
 int /*<<< orphan*/ * phpdbg_find_breakpoint_method (TYPE_1__*) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_tolower (scalar_t__) ; 

__attribute__((used)) static inline phpdbg_breakbase_t *phpdbg_find_breakpoint_symbol(zend_function *fbc) /* {{{ */
{
	zend_op_array *ops;

	if (fbc->type != ZEND_USER_FUNCTION) {
		return NULL;
	}

	ops = (zend_op_array *) fbc;

	if (ops->scope) {
		/* find method breaks here */
		return phpdbg_find_breakpoint_method(ops);
	}

	if (ops->function_name) {
		phpdbg_breakbase_t *brake;
		zend_string *fname = zend_string_tolower(ops->function_name);

		brake = zend_hash_find_ptr(&PHPDBG_G(bp)[PHPDBG_BREAK_SYM], fname);

		zend_string_release(fname);
		return brake;
	} else {
		return zend_hash_str_find_ptr(&PHPDBG_G(bp)[PHPDBG_BREAK_SYM], ZEND_STRL("main"));
	}
}