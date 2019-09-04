#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  inner_scope; } ;
typedef  TYPE_1__ scope_t ;

/* Variables and functions */
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_patch (TYPE_1__*,int) ; 
 int /*<<< orphan*/  scope_links ; 

__attribute__((used)) static void
dump_scope(scope_t *scope)
{
	scope_t *cur_scope;

	/*
	 * Emit the first patch for this scope
	 */
	emit_patch(scope, 0);

	/*
	 * Dump each scope within this one.
	 */
	cur_scope = TAILQ_FIRST(&scope->inner_scope);

	while (cur_scope != NULL) {

		dump_scope(cur_scope);

		cur_scope = TAILQ_NEXT(cur_scope, scope_links);
	}

	/*
	 * Emit the second, closing, patch for this scope
	 */
	emit_patch(scope, 1);
}