#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * v; int /*<<< orphan*/  owned; } ;
typedef  TYPE_1__ variant_val_t ;
typedef  int /*<<< orphan*/  exec_ctx_t ;
typedef  int /*<<< orphan*/  VARIANT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int VT_BYREF ; 
 int VT_VARIANT ; 
 int /*<<< orphan*/ * V_VARIANTREF (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stack_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stack_pop_deref(exec_ctx_t *ctx, variant_val_t *r)
{
    VARIANT *v;

    v = stack_pop(ctx);
    if(V_VT(v) == (VT_BYREF|VT_VARIANT)) {
        r->owned = FALSE;
        r->v = V_VARIANTREF(v);
    }else {
        r->owned = TRUE;
        r->v = v;
    }
}