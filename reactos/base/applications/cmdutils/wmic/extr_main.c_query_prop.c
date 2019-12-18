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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int ULONG ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  int /*<<< orphan*/  IWbemLocator ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WbemLocator ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoInitializeSecurity (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  EOAC_NONE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IWbemLocator ; 
 scalar_t__ IWbemClassObject_Get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemLocator_ConnectServer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWbemLocator_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemServices_ExecQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWbemServices_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_C_AUTHN_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  RPC_C_IMP_LEVEL_IMPERSONATE ; 
 int /*<<< orphan*/  STRING_INVALID_QUERY ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * SysAllocString (char const*) ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VT_BSTR ; 
 char const* V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantChangeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int WBEM_FLAG_FORWARD_ONLY ; 
 int WBEM_FLAG_RETURN_IMMEDIATELY ; 
 int /*<<< orphan*/  WBEM_INFINITE ; 
 scalar_t__ WBEM_S_NO_ERROR ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 char* find_prop (int /*<<< orphan*/ *,char const*) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_header (char*,int) ; 
 int /*<<< orphan*/  output_line (char const*,int) ; 
 int /*<<< orphan*/  strcatW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlenW (char const*) ; 

__attribute__((used)) static int query_prop( const WCHAR *class, const WCHAR *propname )
{
    static const WCHAR select_allW[] = {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',0};
    static const WCHAR cimv2W[] = {'R','O','O','T','\\','C','I','M','V','2',0};
    static const WCHAR wqlW[] = {'W','Q','L',0};
    HRESULT hr;
    IWbemLocator *locator = NULL;
    IWbemServices *services = NULL;
    IEnumWbemClassObject *result = NULL;
    LONG flags = WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY;
    BSTR path = NULL, wql = NULL, query = NULL;
    WCHAR *prop = NULL;
    BOOL first = TRUE;
    int len, ret = -1;
    IWbemClassObject *obj;
    ULONG count, width = 0;
    VARIANT v;

    WINE_TRACE("%s, %s\n", debugstr_w(class), debugstr_w(propname));

    CoInitialize( NULL );
    CoInitializeSecurity( NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT,
                          RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL );

    hr = CoCreateInstance( &CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, &IID_IWbemLocator,
                           (void **)&locator );
    if (hr != S_OK) goto done;

    if (!(path = SysAllocString( cimv2W ))) goto done;
    hr = IWbemLocator_ConnectServer( locator, path, NULL, NULL, NULL, 0, NULL, NULL, &services );
    if (hr != S_OK) goto done;

    len = strlenW( class ) + ARRAY_SIZE(select_allW);
    if (!(query = SysAllocStringLen( NULL, len ))) goto done;
    strcpyW( query, select_allW );
    strcatW( query, class );

    if (!(wql = SysAllocString( wqlW ))) goto done;
    hr = IWbemServices_ExecQuery( services, wql, query, flags, NULL, &result );
    if (hr != S_OK) goto done;

    for (;;) /* get column width */
    {
        IEnumWbemClassObject_Next( result, WBEM_INFINITE, 1, &obj, &count );
        if (!count) break;

        if (!prop && !(prop = find_prop( obj, propname )))
        {
            output_error( STRING_INVALID_QUERY );
            goto done;
        }
        if (IWbemClassObject_Get( obj, prop, 0, &v, NULL, NULL ) == WBEM_S_NO_ERROR)
        {
            VariantChangeType( &v, &v, 0, VT_BSTR );
            width = max( strlenW( V_BSTR( &v ) ), width );
            VariantClear( &v );
        }
        IWbemClassObject_Release( obj );
    }
    width += 2;

    IEnumWbemClassObject_Reset( result );
    for (;;)
    {
        IEnumWbemClassObject_Next( result, WBEM_INFINITE, 1, &obj, &count );
        if (!count) break;

        if (first)
        {
            output_header( prop, width );
            first = FALSE;
        }
        if (IWbemClassObject_Get( obj, prop, 0, &v, NULL, NULL ) == WBEM_S_NO_ERROR)
        {
            VariantChangeType( &v, &v, 0, VT_BSTR );
            output_line( V_BSTR( &v ), width );
            VariantClear( &v );
        }
        IWbemClassObject_Release( obj );
    }
    ret = 0;

done:
    if (result) IEnumWbemClassObject_Release( result );
    if (services) IWbemServices_Release( services );
    if (locator) IWbemLocator_Release( locator );
    SysFreeString( path );
    SysFreeString( query );
    SysFreeString( wql );
    HeapFree( GetProcessHeap(), 0, prop );
    CoUninitialize();
    return ret;
}