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
struct ra_d3d11 {scalar_t__ D3DCompile; int /*<<< orphan*/  d3d_compiler_ver; } ;
struct ra {struct ra_d3d11* priv; } ;
typedef  scalar_t__ pD3DCompile ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ IsWindows8Point1OrGreater () ; 
 int /*<<< orphan*/  LOAD_LIBRARY_SEARCH_SYSTEM32 ; 
 int /*<<< orphan*/ * LoadLibraryExW (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadLibraryW (char*) ; 
 int /*<<< orphan*/  get_dll_version (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load_d3d_compiler(struct ra *ra)
{
    struct ra_d3d11 *p = ra->priv;
    HMODULE d3dcompiler = NULL;

    // Try the inbox D3DCompiler first (Windows 8.1 and up)
    if (IsWindows8Point1OrGreater()) {
        d3dcompiler = LoadLibraryExW(L"d3dcompiler_47.dll", NULL,
                                     LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    // Check for a packaged version of d3dcompiler_47.dll
    if (!d3dcompiler)
        d3dcompiler = LoadLibraryW(L"d3dcompiler_47.dll");
    // Try d3dcompiler_46.dll from the Windows 8 SDK
    if (!d3dcompiler)
        d3dcompiler = LoadLibraryW(L"d3dcompiler_46.dll");
    // Try d3dcompiler_43.dll from the June 2010 DirectX SDK
    if (!d3dcompiler)
        d3dcompiler = LoadLibraryW(L"d3dcompiler_43.dll");
    // Can't find any compiler DLL, so give up
    if (!d3dcompiler)
        return false;

    p->d3d_compiler_ver = get_dll_version(d3dcompiler);

    p->D3DCompile = (pD3DCompile)GetProcAddress(d3dcompiler, "D3DCompile");
    if (!p->D3DCompile)
        return false;
    return true;
}