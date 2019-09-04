#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int op; } ;
typedef  TYPE_1__ php_output_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_output_context_dtor (TYPE_1__*) ; 

__attribute__((used)) static inline void php_output_context_reset(php_output_context *context)
{
	int op = context->op;
	php_output_context_dtor(context);
	memset(context, 0, sizeof(php_output_context));
	context->op = op;
}