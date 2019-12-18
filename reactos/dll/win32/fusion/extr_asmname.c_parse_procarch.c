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
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  pekind; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ IAssemblyNameImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSION_E_INVALID_NAME ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  peAMD64 ; 
 int /*<<< orphan*/  peI386 ; 
 int /*<<< orphan*/  peIA64 ; 
 int /*<<< orphan*/  peMSIL ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT parse_procarch(IAssemblyNameImpl *name, LPCWSTR procarch)
{
    static const WCHAR msilW[] = {'m','s','i','l',0};
    static const WCHAR x86W[] = {'x','8','6',0};
    static const WCHAR ia64W[] = {'i','a','6','4',0};
    static const WCHAR amd64W[] = {'a','m','d','6','4',0};

    if (!lstrcmpiW(procarch, msilW))
        name->pekind = peMSIL;
    else if (!lstrcmpiW(procarch, x86W))
        name->pekind = peI386;
    else if (!lstrcmpiW(procarch, ia64W))
        name->pekind = peIA64;
    else if (!lstrcmpiW(procarch, amd64W))
        name->pekind = peAMD64;
    else
    {
        ERR("unrecognized architecture: %s\n", wine_dbgstr_w(procarch));
        return FUSION_E_INVALID_NAME;
    }

    return S_OK;
}