#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  inner_scope; } ;
typedef  TYPE_1__ scope_t ;
struct TYPE_8__ {int /*<<< orphan*/  inner_scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 TYPE_6__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scope_links ; 
 int /*<<< orphan*/  scope_stack ; 
 int /*<<< orphan*/  scope_stack_links ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 

scope_t *
scope_alloc()
{
	scope_t *new_scope;

	new_scope = (scope_t *)malloc(sizeof(scope_t));
	if (new_scope == NULL)
		stop("Unable to malloc scope object", EX_SOFTWARE);
	memset(new_scope, 0, sizeof(*new_scope));
	TAILQ_INIT(&new_scope->inner_scope);
	
	if (SLIST_FIRST(&scope_stack) != NULL) {
		TAILQ_INSERT_TAIL(&SLIST_FIRST(&scope_stack)->inner_scope,
				  new_scope, scope_links);
	}
	/* This patch is now the current scope */
	SLIST_INSERT_HEAD(&scope_stack, new_scope, scope_stack_links);
	return new_scope;
}