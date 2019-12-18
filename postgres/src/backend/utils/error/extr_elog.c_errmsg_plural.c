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
struct TYPE_3__ {char const* message_id; int /*<<< orphan*/  domain; int /*<<< orphan*/  assoc_context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STACK_DEPTH () ; 
 int /*<<< orphan*/  EVALUATE_MESSAGE_PLURAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_1__* errordata ; 
 size_t errordata_stack_depth ; 
 int /*<<< orphan*/  message ; 
 int /*<<< orphan*/  recursion_depth ; 

int
errmsg_plural(const char *fmt_singular, const char *fmt_plural,
			  unsigned long n,...)
{
	ErrorData  *edata = &errordata[errordata_stack_depth];
	MemoryContext oldcontext;

	recursion_depth++;
	CHECK_STACK_DEPTH();
	oldcontext = MemoryContextSwitchTo(edata->assoc_context);

	edata->message_id = fmt_singular;
	EVALUATE_MESSAGE_PLURAL(edata->domain, message, false);

	MemoryContextSwitchTo(oldcontext);
	recursion_depth--;
	return 0;					/* return value does not matter */
}