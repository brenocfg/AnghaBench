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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int /*<<< orphan*/  atend; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ EnumeratorInstance ;

/* Variables and functions */
 int /*<<< orphan*/  JS_E_ENUMERATOR_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* enumerator_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Enumerator_atEnd(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    EnumeratorInstance *This;

    if (!(This = enumerator_this(jsthis)))
        return throw_type_error(ctx, JS_E_ENUMERATOR_EXPECTED, NULL);

    TRACE("%d\n", This->atend);

    if (r)
        *r = jsval_bool(This->atend);
    return S_OK;
}