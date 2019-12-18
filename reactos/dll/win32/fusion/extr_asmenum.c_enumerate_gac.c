#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  assemblies; } ;
struct TYPE_7__ {scalar_t__ wProcessorArchitecture; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
typedef  TYPE_3__ SYSTEM_INFO ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  TYPE_4__ IAssemblyEnumImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_CACHE_ROOT ; 
 int /*<<< orphan*/  ASM_CACHE_ROOT_EX ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCachePath (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  GetNativeSystemInfo (TYPE_3__*) ; 
 int MAX_PATH ; 
 scalar_t__ PROCESSOR_ARCHITECTURE_AMD64 ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  enum_gac_assemblies (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 

__attribute__((used)) static HRESULT enumerate_gac(IAssemblyEnumImpl *asmenum, IAssemblyName *pName)
{
    static const WCHAR gac[] = {'\\','G','A','C',0};
    static const WCHAR gac_32[] = {'\\','G','A','C','_','3','2',0};
    static const WCHAR gac_64[] = {'\\','G','A','C','_','6','4',0};
    static const WCHAR gac_msil[] = {'\\','G','A','C','_','M','S','I','L',0};
    static const WCHAR v40[] = {'v','4','.','0','_',0};
    WCHAR path[MAX_PATH], buf[MAX_PATH];
    SYSTEM_INFO info;
    HRESULT hr;
    DWORD size;

    size = MAX_PATH;
    hr = GetCachePath(ASM_CACHE_ROOT_EX, buf, &size);
    if (FAILED(hr))
        return hr;

    lstrcpyW(path, buf);
    GetNativeSystemInfo(&info);
    if (info.u.s.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
    {
        lstrcpyW(path + size - 1, gac_64);
        hr = enum_gac_assemblies(&asmenum->assemblies, pName, 0, v40, path);
        if (FAILED(hr))
            return hr;
    }
    lstrcpyW(path + size - 1, gac_32);
    hr = enum_gac_assemblies(&asmenum->assemblies, pName, 0, v40, path);
    if (FAILED(hr))
        return hr;

    lstrcpyW(path + size - 1, gac_msil);
    hr = enum_gac_assemblies(&asmenum->assemblies, pName, 0, v40, path);
    if (FAILED(hr))
        return hr;

    size = MAX_PATH;
    hr = GetCachePath(ASM_CACHE_ROOT, buf, &size);
    if (FAILED(hr))
        return hr;

    lstrcpyW(path, buf);
    if (info.u.s.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
    {
        lstrcpyW(path + size - 1, gac_64);
        hr = enum_gac_assemblies(&asmenum->assemblies, pName, 0, NULL, path);
        if (FAILED(hr))
            return hr;
    }
    lstrcpyW(path + size - 1, gac_32);
    hr = enum_gac_assemblies(&asmenum->assemblies, pName, 0, NULL, path);
    if (FAILED(hr))
        return hr;

    lstrcpyW(path + size - 1, gac_msil);
    hr = enum_gac_assemblies(&asmenum->assemblies, pName, 0, NULL, path);
    if (FAILED(hr))
        return hr;

    lstrcpyW(path + size - 1, gac);
    hr = enum_gac_assemblies(&asmenum->assemblies, pName, 0, NULL, path);
    if (FAILED(hr))
        return hr;

    return S_OK;
}