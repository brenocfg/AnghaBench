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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_UINT32 ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_Put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_SpawnInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PARAM_OUT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_serviceW ; 
 scalar_t__ create_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  method_startserviceW ; 
 int /*<<< orphan*/  param_returnvalueW ; 
 int /*<<< orphan*/  prop_nameW ; 
 scalar_t__ start_service (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT service_start_service( IWbemClassObject *obj, IWbemClassObject *in, IWbemClassObject **out )
{
    VARIANT name, retval;
    IWbemClassObject *sig, *out_params = NULL;
    HRESULT hr;

    TRACE("%p, %p, %p\n", obj, in, out);

    hr = IWbemClassObject_Get( obj, prop_nameW, 0, &name, NULL, NULL );
    if (hr != S_OK) return hr;

    hr = create_signature( class_serviceW, method_startserviceW, PARAM_OUT, &sig );
    if (hr != S_OK)
    {
        VariantClear( &name );
        return hr;
    }
    if (out)
    {
        hr = IWbemClassObject_SpawnInstance( sig, 0, &out_params );
        if (hr != S_OK)
        {
            VariantClear( &name );
            IWbemClassObject_Release( sig );
            return hr;
        }
    }
    hr = start_service( V_BSTR(&name), &retval );
    if (hr != S_OK) goto done;

    if (out_params)
        hr = IWbemClassObject_Put( out_params, param_returnvalueW, 0, &retval, CIM_UINT32 );

done:
    VariantClear( &name );
    IWbemClassObject_Release( sig );
    if (hr == S_OK && out)
    {
        *out = out_params;
        IWbemClassObject_AddRef( out_params );
    }
    if (out_params) IWbemClassObject_Release( out_params );
    return hr;
}