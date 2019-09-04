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
typedef  scalar_t__ tristate ;
struct TYPE_4__ {struct expr* expr; } ;
struct TYPE_3__ {struct expr* expr; } ;
struct expr {scalar_t__ type; TYPE_2__ right; TYPE_1__ left; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_NONE ; 
 scalar_t__ E_OR ; 
 scalar_t__ expr_calc_value (struct expr*) ; 
 int /*<<< orphan*/  expr_print (struct expr*,void (*) (void*,struct symbol*,char const*),void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void expr_print_revdep(struct expr *e,
			      void (*fn)(void *, struct symbol *, const char *),
			      void *data, tristate pr_type, const char **title)
{
	if (e->type == E_OR) {
		expr_print_revdep(e->left.expr, fn, data, pr_type, title);
		expr_print_revdep(e->right.expr, fn, data, pr_type, title);
	} else if (expr_calc_value(e) == pr_type) {
		if (*title) {
			fn(data, NULL, *title);
			*title = NULL;
		}

		fn(data, NULL, "  - ");
		expr_print(e, fn, data, E_NONE);
		fn(data, NULL, "\n");
	}
}