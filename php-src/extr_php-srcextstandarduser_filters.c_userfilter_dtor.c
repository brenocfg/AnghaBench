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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  abstract; } ;
typedef  TYPE_1__ php_stream_filter ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void userfilter_dtor(php_stream_filter *thisfilter)
{
	zval *obj = &thisfilter->abstract;
	zval func_name;
	zval retval;

	if (obj == NULL) {
		/* If there's no object associated then there's nothing to dispose of */
		return;
	}

	ZVAL_STRINGL(&func_name, "onclose", sizeof("onclose")-1);

	call_user_function(NULL,
			obj,
			&func_name,
			&retval,
			0, NULL);

	zval_ptr_dtor(&retval);
	zval_ptr_dtor(&func_name);

	/* kill the object */
	zval_ptr_dtor(obj);
}