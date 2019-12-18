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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_local_assembly_path (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_assemblies_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LONG open_local_assembly_key( UINT context, BOOL win32, const WCHAR *filename, HKEY *hkey )
{
    LONG res;
    HKEY root;
    WCHAR *path;

    if (!(path = build_local_assembly_path( filename )))
        return ERROR_OUTOFMEMORY;

    if ((res = open_assemblies_key( context, win32, &root )))
    {
        msi_free( path );
        return res;
    }
    res = RegCreateKeyW( root, path, hkey );
    RegCloseKey( root );
    msi_free( path );
    return res;
}