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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int /*<<< orphan*/  function_name; TYPE_1__* scope; } ;
typedef  TYPE_2__ zend_op_array ;
typedef  int /*<<< orphan*/  phpdbg_breakbase_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 size_t PHPDBG_BREAK_METHOD ; 
 int /*<<< orphan*/ * PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp ; 
 void* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline phpdbg_breakbase_t *phpdbg_find_breakpoint_method(zend_op_array *ops) /* {{{ */
{
	HashTable *class_table;
	phpdbg_breakbase_t *brake = NULL;
	zend_string *class_lcname = zend_string_tolower(ops->scope->name);

	if ((class_table = zend_hash_find_ptr(&PHPDBG_G(bp)[PHPDBG_BREAK_METHOD], class_lcname))) {
		zend_string *lcname = zend_string_tolower(ops->function_name);

		brake = zend_hash_find_ptr(class_table, lcname);

		zend_string_release(lcname);
	}

	zend_string_release(class_lcname);
	return brake;
}