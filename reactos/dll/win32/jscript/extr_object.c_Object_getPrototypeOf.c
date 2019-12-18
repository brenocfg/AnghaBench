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
struct TYPE_3__ {scalar_t__ prototype; } ;
typedef  TYPE_1__ jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_addref (scalar_t__) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_jsdisp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Object_getPrototypeOf(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags,
                                     unsigned argc, jsval_t *argv, jsval_t *r)
{
    jsdisp_t *obj;

    if(!argc || !is_object_instance(argv[0])) {
        FIXME("invalid arguments\n");
        return E_NOTIMPL;
    }

    TRACE("(%s)\n", debugstr_jsval(argv[1]));

    obj = to_jsdisp(get_object(argv[0]));
    if(!obj) {
        FIXME("Non-JS object\n");
        return E_NOTIMPL;
    }

    if(r)
        *r = obj->prototype
            ? jsval_obj(jsdisp_addref(obj->prototype))
            : jsval_null();
    return S_OK;
}