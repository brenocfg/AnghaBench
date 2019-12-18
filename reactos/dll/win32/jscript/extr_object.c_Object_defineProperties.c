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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_define_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/ * to_jsdisp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Object_defineProperties(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags,
                                     unsigned argc, jsval_t *argv, jsval_t *r)
{
    jsdisp_t *obj;
    HRESULT hres;

    if(argc < 1 || !is_object_instance(argv[0]) || !get_object(argv[0]) || !(obj = to_jsdisp(get_object(argv[0])))) {
        FIXME("not an object\n");
        return E_NOTIMPL;
    }

    TRACE("%p\n", obj);

    hres = jsdisp_define_properties(ctx, obj, argc >= 2 ? argv[1] : jsval_undefined());
    if(SUCCEEDED(hres) && r)
        *r = jsval_obj(jsdisp_addref(obj));
    return hres;
}