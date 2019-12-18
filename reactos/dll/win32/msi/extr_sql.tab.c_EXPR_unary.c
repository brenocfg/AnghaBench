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
struct TYPE_3__ {int /*<<< orphan*/ * right; int /*<<< orphan*/  op; struct expr* left; } ;
struct TYPE_4__ {TYPE_1__ expr; } ;
struct expr {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_UNARY ; 
 struct expr* parser_alloc (void*,int) ; 

__attribute__((used)) static struct expr * EXPR_unary( void *info, struct expr *l, UINT op )
{
    struct expr *e = parser_alloc( info, sizeof *e );
    if( e )
    {
        e->type = EXPR_UNARY;
        e->u.expr.left = l;
        e->u.expr.op = op;
        e->u.expr.right = NULL;
    }
    return e;
}