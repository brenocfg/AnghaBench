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

/* Variables and functions */
 int CONST_CS ; 
 int CONST_PERSISTENT ; 
 int /*<<< orphan*/  DEBUG_BACKTRACE_IGNORE_ARGS ; 
 int /*<<< orphan*/  DEBUG_BACKTRACE_PROVIDE_OBJECT ; 
 int /*<<< orphan*/  E_ALL ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  E_COMPILE_WARNING ; 
 int /*<<< orphan*/  E_CORE_ERROR ; 
 int /*<<< orphan*/  E_CORE_WARNING ; 
 int /*<<< orphan*/  E_DEPRECATED ; 
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  E_NOTICE ; 
 int /*<<< orphan*/  E_PARSE ; 
 int /*<<< orphan*/  E_RECOVERABLE_ERROR ; 
 int /*<<< orphan*/  E_STRICT ; 
 int /*<<< orphan*/  E_USER_DEPRECATED ; 
 int /*<<< orphan*/  E_USER_ERROR ; 
 int /*<<< orphan*/  E_USER_NOTICE ; 
 int /*<<< orphan*/  E_USER_WARNING ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  REGISTER_MAIN_BOOL_CONSTANT (char*,int,int) ; 
 int /*<<< orphan*/  REGISTER_MAIN_LONG_CONSTANT (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REGISTER_MAIN_NULL_CONSTANT (char*,int) ; 
 int ZEND_DEBUG ; 
 int ZTS_V ; 
 int /*<<< orphan*/  ZVAL_FALSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_TRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  false_value ; 
 int /*<<< orphan*/  null_value ; 
 int /*<<< orphan*/  true_value ; 

void zend_register_standard_constants(void)
{
	REGISTER_MAIN_LONG_CONSTANT("E_ERROR", E_ERROR, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_RECOVERABLE_ERROR", E_RECOVERABLE_ERROR, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_WARNING", E_WARNING, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_PARSE", E_PARSE, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_NOTICE", E_NOTICE, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_STRICT", E_STRICT, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_DEPRECATED", E_DEPRECATED, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_CORE_ERROR", E_CORE_ERROR, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_CORE_WARNING", E_CORE_WARNING, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_COMPILE_ERROR", E_COMPILE_ERROR, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_COMPILE_WARNING", E_COMPILE_WARNING, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_USER_ERROR", E_USER_ERROR, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_USER_WARNING", E_USER_WARNING, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_USER_NOTICE", E_USER_NOTICE, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("E_USER_DEPRECATED", E_USER_DEPRECATED, CONST_PERSISTENT | CONST_CS);

	REGISTER_MAIN_LONG_CONSTANT("E_ALL", E_ALL, CONST_PERSISTENT | CONST_CS);

	REGISTER_MAIN_LONG_CONSTANT("DEBUG_BACKTRACE_PROVIDE_OBJECT", DEBUG_BACKTRACE_PROVIDE_OBJECT, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_LONG_CONSTANT("DEBUG_BACKTRACE_IGNORE_ARGS", DEBUG_BACKTRACE_IGNORE_ARGS, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_BOOL_CONSTANT("ZEND_THREAD_SAFE", ZTS_V, CONST_PERSISTENT | CONST_CS);
	REGISTER_MAIN_BOOL_CONSTANT("ZEND_DEBUG_BUILD", ZEND_DEBUG, CONST_PERSISTENT | CONST_CS);

	/* Special constants true/false/null.  */
	REGISTER_MAIN_BOOL_CONSTANT("TRUE", 1, CONST_PERSISTENT);
	REGISTER_MAIN_BOOL_CONSTANT("FALSE", 0, CONST_PERSISTENT);
	REGISTER_MAIN_NULL_CONSTANT("NULL", CONST_PERSISTENT);

	ZVAL_NULL(&null_value);
	ZVAL_TRUE(&true_value);
	ZVAL_FALSE(&false_value);
}