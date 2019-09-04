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
typedef  int php_output_handler_status_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  level; } ;
typedef  TYPE_1__ php_output_handler ;
typedef  int /*<<< orphan*/  php_output_context ;

/* Variables and functions */
 int PHP_OUTPUT_HANDLER_DISABLED ; 
#define  PHP_OUTPUT_HANDLER_FAILURE 130 
#define  PHP_OUTPUT_HANDLER_NO_DATA 129 
#define  PHP_OUTPUT_HANDLER_SUCCESS 128 
 int /*<<< orphan*/  php_output_context_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_output_context_swap (int /*<<< orphan*/ *) ; 
 int php_output_handler_op (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_output_stack_apply_op(void *h, void *c)
{
	int was_disabled;
	php_output_handler_status_t status;
	php_output_handler *handler = *(php_output_handler **) h;
	php_output_context *context = (php_output_context *) c;

	if ((was_disabled = (handler->flags & PHP_OUTPUT_HANDLER_DISABLED))) {
		status = PHP_OUTPUT_HANDLER_FAILURE;
	} else {
		status = php_output_handler_op(handler, context);
	}

	/*
	 * handler ate all => break
	 * handler returned data or failed resp. is disabled => continue
	 */
	switch (status) {
		case PHP_OUTPUT_HANDLER_NO_DATA:
			return 1;

		case PHP_OUTPUT_HANDLER_SUCCESS:
			/* swap contexts buffers, unless this is the last handler in the stack */
			if (handler->level) {
				php_output_context_swap(context);
			}
			return 0;

		case PHP_OUTPUT_HANDLER_FAILURE:
		default:
			if (was_disabled) {
				/* pass input along, if it's the last handler in the stack */
				if (!handler->level) {
					php_output_context_pass(context);
				}
			} else {
				/* swap buffers, unless this is the last handler */
				if (handler->level) {
					php_output_context_swap(context);
				}
			}
			return 0;
	}
}