#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  site; TYPE_5__* named_items; scalar_t__ global; TYPE_1__* call_ctx; } ;
typedef  TYPE_3__ script_ctx_t ;
struct TYPE_23__ {int /*<<< orphan*/  obj; scalar_t__ jsobj; TYPE_11__* frame; struct TYPE_23__* next; } ;
typedef  TYPE_4__ scope_chain_t ;
struct TYPE_24__ {int flags; char const* name; int /*<<< orphan*/  disp; struct TYPE_24__* next; } ;
typedef  TYPE_5__ named_item_t ;
struct TYPE_25__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_6__ local_ref_t ;
typedef  int /*<<< orphan*/  function_code_t ;
struct TYPE_21__ {int /*<<< orphan*/  val; int /*<<< orphan*/  off; } ;
struct TYPE_26__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_7__ exprval_t ;
typedef  char WCHAR ;
struct TYPE_20__ {TYPE_4__* scope; } ;
struct TYPE_19__ {int /*<<< orphan*/ * function; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  char const* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EXPRVAL_JSVAL ; 
 int /*<<< orphan*/  EXPRVAL_STACK_REF ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IActiveScriptSite_GetItemInfo (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JS_E_UNDEFINED_VARIABLE ; 
 int /*<<< orphan*/  SCRIPTINFO_IUNKNOWN ; 
 int SCRIPTITEM_ISVISIBLE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  detach_variable_object (TYPE_3__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disp_get_id (TYPE_3__*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprval_set_disp_ref (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprval_set_exception (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdexNameImplicit ; 
 int /*<<< orphan*/  jsdisp_get_id (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_off (TYPE_11__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_global_members (TYPE_3__*,char const*,TYPE_7__*) ; 
 TYPE_6__* lookup_local (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  to_disp (scalar_t__) ; 
 int /*<<< orphan*/  wcscmp (char const*,char const*) ; 

__attribute__((used)) static HRESULT identifier_eval(script_ctx_t *ctx, BSTR identifier, exprval_t *ret)
{
    scope_chain_t *scope;
    named_item_t *item;
    DISPID id = 0;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(identifier));

    if(ctx->call_ctx) {
        for(scope = ctx->call_ctx->scope; scope; scope = scope->next) {
            if(scope->frame) {
                function_code_t *func = scope->frame->function;
                local_ref_t *ref = lookup_local(func, identifier);
                static const WCHAR argumentsW[] = {'a','r','g','u','m','e','n','t','s',0};

                if(ref) {
                    ret->type = EXPRVAL_STACK_REF;
                    ret->u.off = local_off(scope->frame, ref->ref);
                    TRACE("returning ref %d for %d\n", ret->u.off, ref->ref);
                    return S_OK;
                }

                if(!wcscmp(identifier, argumentsW)) {
                    hres = detach_variable_object(ctx, scope->frame, FALSE);
                    if(FAILED(hres))
                        return hres;
                }
            }
            if(scope->jsobj)
                hres = jsdisp_get_id(scope->jsobj, identifier, fdexNameImplicit, &id);
            else
                hres = disp_get_id(ctx, scope->obj, identifier, identifier, fdexNameImplicit, &id);
            if(SUCCEEDED(hres)) {
                exprval_set_disp_ref(ret, scope->obj, id);
                return S_OK;
            }
        }
    }

    hres = jsdisp_get_id(ctx->global, identifier, 0, &id);
    if(SUCCEEDED(hres)) {
        exprval_set_disp_ref(ret, to_disp(ctx->global), id);
        return S_OK;
    }

    for(item = ctx->named_items; item; item = item->next) {
        if((item->flags & SCRIPTITEM_ISVISIBLE) && !wcscmp(item->name, identifier)) {
            if(!item->disp) {
                IUnknown *unk;

                if(!ctx->site)
                    break;

                hres = IActiveScriptSite_GetItemInfo(ctx->site, identifier,
                                                     SCRIPTINFO_IUNKNOWN, &unk, NULL);
                if(FAILED(hres)) {
                    WARN("GetItemInfo failed: %08x\n", hres);
                    break;
                }

                hres = IUnknown_QueryInterface(unk, &IID_IDispatch, (void**)&item->disp);
                IUnknown_Release(unk);
                if(FAILED(hres)) {
                    WARN("object does not implement IDispatch\n");
                    break;
                }
            }

            IDispatch_AddRef(item->disp);
            ret->type = EXPRVAL_JSVAL;
            ret->u.val = jsval_disp(item->disp);
            return S_OK;
        }
    }

    if(lookup_global_members(ctx, identifier, ret))
        return S_OK;

    exprval_set_exception(ret, JS_E_UNDEFINED_VARIABLE);
    return S_OK;
}