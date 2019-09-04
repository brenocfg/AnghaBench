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
typedef  int /*<<< orphan*/  tristate ;
struct gstr {int dummy; } ;
struct expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  expr_print_gstr_helper ; 
 int /*<<< orphan*/  expr_print_revdep (struct expr*,int /*<<< orphan*/ ,struct gstr*,int /*<<< orphan*/ ,char const**) ; 

void expr_gstr_print_revdep(struct expr *e, struct gstr *gs,
			    tristate pr_type, const char *title)
{
	expr_print_revdep(e, expr_print_gstr_helper, gs, pr_type, &title);
}