#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int cbAssemblyInfo; scalar_t__ dwAssemblyFlags; } ;
typedef  int /*<<< orphan*/  IAssemblyCache ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;
typedef  TYPE_1__ ASSEMBLY_INFO ;

/* Variables and functions */
 scalar_t__ ASSEMBLYINFO_FLAG_INSTALLED ; 
 scalar_t__ E_NOT_SUFFICIENT_BUFFER ; 
 int FALSE ; 
 scalar_t__ IAssemblyCache_QueryAssemblyInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL is_assembly_installed( IAssemblyCache *cache, const WCHAR *display_name )
{
    HRESULT hr;
    ASSEMBLY_INFO info;

    if (!cache) return FALSE;

    memset( &info, 0, sizeof(info) );
    info.cbAssemblyInfo = sizeof(info);
    hr = IAssemblyCache_QueryAssemblyInfo( cache, 0, display_name, &info );
    if (hr == S_OK /* sxs version */ || hr == E_NOT_SUFFICIENT_BUFFER)
    {
        return (info.dwAssemblyFlags == ASSEMBLYINFO_FLAG_INSTALLED);
    }
    TRACE("QueryAssemblyInfo returned 0x%08x\n", hr);
    return FALSE;
}