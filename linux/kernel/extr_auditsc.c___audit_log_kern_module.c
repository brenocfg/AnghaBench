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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct audit_context {int /*<<< orphan*/  type; TYPE_1__ module; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_KERN_MODULE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct audit_context* audit_context () ; 
 int /*<<< orphan*/  audit_log_lost (char*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 

void __audit_log_kern_module(char *name)
{
	struct audit_context *context = audit_context();

	context->module.name = kstrdup(name, GFP_KERNEL);
	if (!context->module.name)
		audit_log_lost("out of memory in __audit_log_kern_module");
	context->type = AUDIT_KERN_MODULE;
}