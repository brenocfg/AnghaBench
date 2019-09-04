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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {TYPE_1__* notifier; } ;
typedef  TYPE_2__ php_stream_context ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ call_user_function_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_space_stream_notifier(php_stream_context *context, int notifycode, int severity,
		char *xmsg, int xcode, size_t bytes_sofar, size_t bytes_max, void * ptr)
{
	zval *callback = &context->notifier->ptr;
	zval retval;
	zval zvs[6];
	int i;

	ZVAL_LONG(&zvs[0], notifycode);
	ZVAL_LONG(&zvs[1], severity);
	if (xmsg) {
		ZVAL_STRING(&zvs[2], xmsg);
	} else {
		ZVAL_NULL(&zvs[2]);
	}
	ZVAL_LONG(&zvs[3], xcode);
	ZVAL_LONG(&zvs[4], bytes_sofar);
	ZVAL_LONG(&zvs[5], bytes_max);

	if (FAILURE == call_user_function_ex(NULL, NULL, callback, &retval, 6, zvs, 0, NULL)) {
		php_error_docref(NULL, E_WARNING, "failed to call user notifier");
	}
	for (i = 0; i < 6; i++) {
		zval_ptr_dtor(&zvs[i]);
	}
	zval_ptr_dtor(&retval);
}