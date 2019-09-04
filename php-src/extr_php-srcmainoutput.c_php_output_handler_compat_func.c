#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* php_output_handler_func_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,size_t*,int /*<<< orphan*/ ) ;
struct TYPE_6__ {char* data; size_t used; int free; } ;
struct TYPE_7__ {int /*<<< orphan*/  used; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ out; int /*<<< orphan*/  op; TYPE_2__ in; } ;
typedef  TYPE_3__ php_output_context ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  php_output_context_pass (TYPE_3__*) ; 

__attribute__((used)) static int php_output_handler_compat_func(void **handler_context, php_output_context *output_context)
{
	php_output_handler_func_t func = *(php_output_handler_func_t *) handler_context;

	if (func) {
		char *out_str = NULL;
		size_t out_len = 0;

		func(output_context->in.data, output_context->in.used, &out_str, &out_len, output_context->op);

		if (out_str) {
			output_context->out.data = out_str;
			output_context->out.used = out_len;
			output_context->out.free = 1;
		} else {
			php_output_context_pass(output_context);
		}

		return SUCCESS;
	}
	return FAILURE;
}