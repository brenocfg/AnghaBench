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
struct linux_binprm {int /*<<< orphan*/  argc; } ;
struct TYPE_2__ {int /*<<< orphan*/  argc; } ;
struct audit_context {TYPE_1__ execve; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_EXECVE ; 
 struct audit_context* audit_context () ; 

void __audit_bprm(struct linux_binprm *bprm)
{
	struct audit_context *context = audit_context();

	context->type = AUDIT_EXECVE;
	context->execve.argc = bprm->argc;
}