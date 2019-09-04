#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* self; } ;
struct acpiphp_context {TYPE_2__ hp; int /*<<< orphan*/  bridge; scalar_t__ refcount; } ;
struct TYPE_3__ {int /*<<< orphan*/ * hp; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpiphp_context*) ; 

__attribute__((used)) static void acpiphp_put_context(struct acpiphp_context *context)
{
	if (--context->refcount)
		return;

	WARN_ON(context->bridge);
	context->hp.self->hp = NULL;
	kfree(context);
}