#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct constraint_expr {struct constraint_expr* type_names; int /*<<< orphan*/  negset; int /*<<< orphan*/  types; int /*<<< orphan*/  names; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebitmap_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct constraint_expr*) ; 

__attribute__((used)) static void constraint_expr_destroy(struct constraint_expr *expr)
{
	if (expr) {
		ebitmap_destroy(&expr->names);
		if (expr->type_names) {
			ebitmap_destroy(&expr->type_names->types);
			ebitmap_destroy(&expr->type_names->negset);
			kfree(expr->type_names);
		}
		kfree(expr);
	}
}