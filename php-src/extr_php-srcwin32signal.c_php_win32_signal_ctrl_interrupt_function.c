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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_execute_data ;

/* Variables and functions */
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_evt ; 
 int /*<<< orphan*/  ctrl_handler ; 
 int /*<<< orphan*/  orig_interrupt_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_win32_signal_ctrl_interrupt_function(zend_execute_data *execute_data)
{/*{{{*/
	if (IS_UNDEF != Z_TYPE(ctrl_handler)) {
		zval retval, params[1];

		ZVAL_LONG(&params[0], ctrl_evt);

		/* If the function returns, */
		call_user_function(NULL, NULL, &ctrl_handler, &retval, 1, params);
		zval_ptr_dtor(&retval);
	}

	if (orig_interrupt_function) {
		orig_interrupt_function(execute_data);
	}
}