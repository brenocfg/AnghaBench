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
struct symbol {int dummy; } ;
struct expr {int dummy; } ;
typedef  enum prop_type { ____Placeholder_prop_type } prop_type ;

/* Variables and functions */
 int /*<<< orphan*/  expr_alloc_symbol (struct symbol*) ; 
 int /*<<< orphan*/  menu_add_prop (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct expr*) ; 

void menu_add_symbol(enum prop_type type, struct symbol *sym, struct expr *dep)
{
	menu_add_prop(type, NULL, expr_alloc_symbol(sym), dep);
}