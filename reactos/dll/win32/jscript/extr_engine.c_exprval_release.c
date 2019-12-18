#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  disp; } ;
struct TYPE_6__ {TYPE_1__ idref; int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ exprval_t ;

/* Variables and functions */
#define  EXPRVAL_IDREF 131 
#define  EXPRVAL_INVALID 130 
#define  EXPRVAL_JSVAL 129 
#define  EXPRVAL_STACK_REF 128 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exprval_release(exprval_t *val)
{
    switch(val->type) {
    case EXPRVAL_JSVAL:
        jsval_release(val->u.val);
        return;
    case EXPRVAL_IDREF:
        if(val->u.idref.disp)
            IDispatch_Release(val->u.idref.disp);
        return;
    case EXPRVAL_STACK_REF:
    case EXPRVAL_INVALID:
        return;
    }
}