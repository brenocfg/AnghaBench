#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nargs; int /*<<< orphan*/  args; } ;
struct audit_context {TYPE_1__ socketcall; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int AUDITSC_ARGS ; 
 int /*<<< orphan*/  AUDIT_SOCKETCALL ; 
 int EINVAL ; 
 struct audit_context* audit_context () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,int) ; 

int __audit_socketcall(int nargs, unsigned long *args)
{
	struct audit_context *context = audit_context();

	if (nargs <= 0 || nargs > AUDITSC_ARGS || !args)
		return -EINVAL;
	context->type = AUDIT_SOCKETCALL;
	context->socketcall.nargs = nargs;
	memcpy(context->socketcall.args, args, nargs * sizeof(unsigned long));
	return 0;
}