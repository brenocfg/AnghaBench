#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_7__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_6__ {int atend; int /*<<< orphan*/  dispex; int /*<<< orphan*/ * enumvar; } ;
typedef  int /*<<< orphan*/  IEnumVARIANT ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ EnumeratorInstance ;
typedef  TYPE_2__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  DISPID_NEWENUM ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IDispatch_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumVARIANT_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IEnumVARIANT ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ VT_UNKNOWN ; 
 int /*<<< orphan*/  V_UNKNOWN (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  alloc_enumerator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  enumvar_get_next_item (TYPE_1__*) ; 
 int /*<<< orphan*/ * get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_enumerator(script_ctx_t *ctx, jsval_t *argv, jsdisp_t **ret)
{
    EnumeratorInstance *enumerator;
    HRESULT hres;
    IDispatch *obj;
    DISPPARAMS dispparams = {NULL, NULL, 0, 0};
    IEnumVARIANT *enumvar = NULL;

    if (argv)
    {
        VARIANT varresult;

        if (!is_object_instance(*argv))
        {
            FIXME("I don't know how to handle this type!\n");
            return E_NOTIMPL;
        }

        obj = get_object(*argv);

        /* Try to get a IEnumVARIANT by _NewEnum */
        VariantInit(&varresult);
        hres = IDispatch_Invoke(obj, DISPID_NEWENUM, &IID_NULL, LOCALE_NEUTRAL,
                DISPATCH_METHOD, &dispparams, &varresult, NULL, NULL);
        if (FAILED(hres))
        {
            WARN("Enumerator: no DISPID_NEWENUM.\n");
            return E_INVALIDARG;
        }

        if ((V_VT(&varresult) == VT_DISPATCH) || (V_VT(&varresult) == VT_UNKNOWN))
        {
            hres = IUnknown_QueryInterface(V_UNKNOWN(&varresult),
                &IID_IEnumVARIANT, (void**)&enumvar);
        }
        else
        {
            FIXME("Enumerator: NewEnum unexpected type of varresult (%d).\n", V_VT(&varresult));
            hres = E_INVALIDARG;
        }
        VariantClear(&varresult);
        if (FAILED(hres))
            return hres;
    }

    hres = alloc_enumerator(ctx, NULL, &enumerator);
    if (FAILED(hres))
    {
        if (enumvar)
            IEnumVARIANT_Release(enumvar);
        return hres;
    }

    enumerator->enumvar = enumvar;
    enumerator->atend = !enumvar;
    hres = enumvar_get_next_item(enumerator);
    if (FAILED(hres))
    {
        jsdisp_release(&enumerator->dispex);
        return hres;
    }

    *ret = &enumerator->dispex;
    return S_OK;
}