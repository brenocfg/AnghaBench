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
struct assembly {int /*<<< orphan*/  version; int /*<<< orphan*/  token; int /*<<< orphan*/  name; int /*<<< orphan*/  arch; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyFileW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_policy_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT install_policy( const WCHAR *manifest, struct assembly *assembly )
{
    WCHAR *dst;
    BOOL ret;

    /* FIXME: handle catalog file */

    dst = build_policy_filename( assembly->arch, assembly->name, assembly->token, assembly->version );
    if (!dst) return E_OUTOFMEMORY;

    ret = CopyFileW( manifest, dst, FALSE );
    HeapFree( GetProcessHeap(), 0, dst );
    if (!ret)
    {
        HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );
        WARN("failed to copy policy manifest file 0x%08x\n", hr);
        return hr;
    }
    return S_OK;
}