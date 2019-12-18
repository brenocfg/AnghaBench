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
struct TYPE_2__ {struct expr* expr; } ;
struct expr {int type; TYPE_1__ left; } ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
 struct expr* xcalloc (int,int) ; 

struct expr *expr_alloc_one(enum expr_type type, struct expr *ce)
{
	struct expr *e = xcalloc(1, sizeof(*e));
	e->type = type;
	e->left.expr = ce;
	return e;
}