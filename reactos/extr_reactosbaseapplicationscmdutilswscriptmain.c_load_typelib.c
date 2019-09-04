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
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IID_IArguments2 ; 
 int /*<<< orphan*/  IID_IHost ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadTypeLib (char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arguments_ti ; 
 int /*<<< orphan*/  host_ti ; 

__attribute__((used)) static BOOL load_typelib(void)
{
    ITypeLib *typelib;
    HRESULT hres;

    static const WCHAR wscript_exeW[] = {'w','s','c','r','i','p','t','.','e','x','e',0};

    hres = LoadTypeLib(wscript_exeW, &typelib);
    if(FAILED(hres))
        return FALSE;

    hres = ITypeLib_GetTypeInfoOfGuid(typelib, &IID_IHost, &host_ti);
    if(SUCCEEDED(hres))
        hres = ITypeLib_GetTypeInfoOfGuid(typelib, &IID_IArguments2, &arguments_ti);

    ITypeLib_Release(typelib);
    return SUCCEEDED(hres);
}