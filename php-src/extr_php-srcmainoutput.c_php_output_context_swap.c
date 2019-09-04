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
struct TYPE_6__ {scalar_t__ size; scalar_t__ free; scalar_t__ used; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ free; scalar_t__ used; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {TYPE_2__ out; TYPE_1__ in; } ;
typedef  TYPE_3__ php_output_context ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void php_output_context_swap(php_output_context *context)
{
	if (context->in.free && context->in.data) {
		efree(context->in.data);
	}
	context->in.data = context->out.data;
	context->in.used = context->out.used;
	context->in.free = context->out.free;
	context->in.size = context->out.size;
	context->out.data = NULL;
	context->out.used = 0;
	context->out.free = 0;
	context->out.size = 0;
}