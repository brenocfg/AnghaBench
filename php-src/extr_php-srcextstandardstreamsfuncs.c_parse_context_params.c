#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {TYPE_2__* notifier; } ;
typedef  TYPE_1__ php_stream_context ;
struct TYPE_7__ {int /*<<< orphan*/  dtor; int /*<<< orphan*/  ptr; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ IS_ARRAY ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_context_options (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* php_stream_notification_alloc () ; 
 int /*<<< orphan*/  php_stream_notification_free (TYPE_2__*) ; 
 int /*<<< orphan*/  user_space_stream_notifier ; 
 int /*<<< orphan*/  user_space_stream_notifier_dtor ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int parse_context_params(php_stream_context *context, zval *params)
{
	int ret = SUCCESS;
	zval *tmp;

	if (NULL != (tmp = zend_hash_str_find(Z_ARRVAL_P(params), "notification", sizeof("notification")-1))) {

		if (context->notifier) {
			php_stream_notification_free(context->notifier);
			context->notifier = NULL;
		}

		context->notifier = php_stream_notification_alloc();
		context->notifier->func = user_space_stream_notifier;
		ZVAL_COPY(&context->notifier->ptr, tmp);
		context->notifier->dtor = user_space_stream_notifier_dtor;
	}
	if (NULL != (tmp = zend_hash_str_find(Z_ARRVAL_P(params), "options", sizeof("options")-1))) {
		if (Z_TYPE_P(tmp) == IS_ARRAY) {
			parse_context_options(context, tmp);
		} else {
			php_error_docref(NULL, E_WARNING, "Invalid stream/context parameter");
		}
	}

	return ret;
}