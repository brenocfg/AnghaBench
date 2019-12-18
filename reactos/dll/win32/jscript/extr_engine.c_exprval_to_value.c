#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_6__ {int /*<<< orphan*/  disp; } ;
struct TYPE_7__ {TYPE_1__ idref; int /*<<< orphan*/  val; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_3__ exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ EXPRVAL_IDREF ; 
 scalar_t__ EXPRVAL_JSVAL ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  exprval_propget (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT exprval_to_value(script_ctx_t *ctx, exprval_t *ref, jsval_t *r)
{
    HRESULT hres;

    if(ref->type == EXPRVAL_JSVAL) {
        *r = ref->u.val;
        return S_OK;
    }

    hres = exprval_propget(ctx, ref, r);

    if(ref->type == EXPRVAL_IDREF)
        IDispatch_Release(ref->u.idref.disp);
    return hres;
}