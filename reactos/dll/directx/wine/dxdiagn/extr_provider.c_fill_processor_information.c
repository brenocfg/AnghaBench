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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  int /*<<< orphan*/  IWbemLocator ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  int /*<<< orphan*/  IDxDiagContainerImpl_Container ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WbemLocator ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IWbemLocator ; 
 int /*<<< orphan*/  IWbemClassObject_Get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemLocator_ConnectServer (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWbemLocator_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemServices_CreateInstanceEnum (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWbemServices_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__) ; 
 char* V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WBEM_FLAG_SYSTEM_ONLY ; 
 int /*<<< orphan*/  add_bstr_property (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT fill_processor_information(IDxDiagContainerImpl_Container *node)
{
    static const WCHAR szProcessorEnglish[] = {'s','z','P','r','o','c','e','s','s','o','r','E','n','g','l','i','s','h',0};

    static const WCHAR cimv2W[] = {'\\','\\','.','\\','r','o','o','t','\\','c','i','m','v','2',0};
    static const WCHAR proc_classW[] = {'W','i','n','3','2','_','P','r','o','c','e','s','s','o','r',0};
    static const WCHAR nameW[] = {'N','a','m','e',0};
    static const WCHAR max_clock_speedW[] = {'M','a','x','C','l','o','c','k','S','p','e','e','d',0};
    static const WCHAR cpu_noW[] = {'N','u','m','b','e','r','O','f','L','o','g','i','c','a','l','P','r','o','c','e','s','s','o','r','s',0};

    static const WCHAR processor_fmtW[] = {'%','s','(','%','d',' ','C','P','U','s',')',',',' ','~','%','d','M','H','z',0};

    IWbemLocator *wbem_locator;
    IWbemServices *wbem_service;
    IWbemClassObject *wbem_class;
    IEnumWbemClassObject *wbem_enum;
    VARIANT cpu_name, cpu_no, clock_speed;
    WCHAR print_buf[200];
    BSTR bstr;
    ULONG no;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, &IID_IWbemLocator, (void**)&wbem_locator);
    if(FAILED(hr))
        return hr;

    bstr = SysAllocString(cimv2W);
    if(!bstr) {
        IWbemLocator_Release(wbem_locator);
        return E_OUTOFMEMORY;
    }
    hr = IWbemLocator_ConnectServer(wbem_locator, bstr, NULL, NULL, NULL, 0, NULL, NULL, &wbem_service);
    IWbemLocator_Release(wbem_locator);
    SysFreeString(bstr);
    if(FAILED(hr))
        return hr;

    bstr = SysAllocString(proc_classW);
    if(!bstr) {
        IWbemServices_Release(wbem_service);
        return E_OUTOFMEMORY;
    }
    hr = IWbemServices_CreateInstanceEnum(wbem_service, bstr, WBEM_FLAG_SYSTEM_ONLY, NULL, &wbem_enum);
    IWbemServices_Release(wbem_service);
    SysFreeString(bstr);
    if(FAILED(hr))
        return hr;

    hr = IEnumWbemClassObject_Next(wbem_enum, 1000, 1, &wbem_class, &no);
    IEnumWbemClassObject_Release(wbem_enum);
    if(FAILED(hr))
        return hr;

    hr = IWbemClassObject_Get(wbem_class, cpu_noW, 0, &cpu_no, NULL, NULL);
    if(FAILED(hr)) {
        IWbemClassObject_Release(wbem_class);
        return hr;
    }
    hr = IWbemClassObject_Get(wbem_class, max_clock_speedW, 0, &clock_speed, NULL, NULL);
    if(FAILED(hr)) {
        IWbemClassObject_Release(wbem_class);
        return hr;
    }
    hr = IWbemClassObject_Get(wbem_class, nameW, 0, &cpu_name, NULL, NULL);
    IWbemClassObject_Release(wbem_class);
    if(FAILED(hr))
        return hr;

    swprintf(print_buf, processor_fmtW,
             V_BSTR(&cpu_name), V_I4(&cpu_no), V_I4(&clock_speed));
    VariantClear(&cpu_name);
    VariantClear(&cpu_no);
    VariantClear(&clock_speed);

    return add_bstr_property(node, szProcessorEnglish, print_buf);
}