#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ op; struct expr* right; struct expr* left; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sval; TYPE_2__* propval; TYPE_1__ expr; } ;
struct expr {scalar_t__ type; TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ EXPR_COMPLEX ; 
 scalar_t__ EXPR_PROPVAL ; 
 scalar_t__ EXPR_SVAL ; 
 scalar_t__ OP_EQ ; 
 int /*<<< orphan*/  prop_sidW ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const WCHAR *find_sid_str( const struct expr *cond )
{
    const struct expr *left, *right;
    const WCHAR *ret = NULL;

    if (!cond || cond->type != EXPR_COMPLEX || cond->u.expr.op != OP_EQ) return NULL;

    left = cond->u.expr.left;
    right = cond->u.expr.right;
    if (left->type == EXPR_PROPVAL && right->type == EXPR_SVAL && !strcmpiW( left->u.propval->name, prop_sidW ))
    {
        ret = right->u.sval;
    }
    else if (left->type == EXPR_SVAL && right->type == EXPR_PROPVAL && !strcmpiW( right->u.propval->name, prop_sidW ))
    {
        ret = left->u.sval;
    }
    return ret;
}