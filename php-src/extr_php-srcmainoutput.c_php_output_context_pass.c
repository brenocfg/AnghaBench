#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; scalar_t__ free; scalar_t__ used; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {scalar_t__ free; scalar_t__ size; scalar_t__ used; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {TYPE_1__ in; TYPE_2__ out; } ;
typedef  TYPE_3__ php_output_context ;

/* Variables and functions */

__attribute__((used)) static inline void php_output_context_pass(php_output_context *context)
{
	context->out.data = context->in.data;
	context->out.used = context->in.used;
	context->out.size = context->in.size;
	context->out.free = context->in.free;
	context->in.data = NULL;
	context->in.used = 0;
	context->in.free = 0;
	context->in.size = 0;
}