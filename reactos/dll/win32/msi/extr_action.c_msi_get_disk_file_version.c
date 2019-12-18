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
typedef  int /*<<< orphan*/  VS_FIXEDFILEINFO ;
typedef  int /*<<< orphan*/  UINT ;
typedef  void* LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetFileVersionInfoSizeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFileVersionInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  VerQueryValueW (void*,char const*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* msi_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (void*) ; 

VS_FIXEDFILEINFO *msi_get_disk_file_version( LPCWSTR filename )
{
    static const WCHAR name[] = {'\\',0};
    VS_FIXEDFILEINFO *ptr, *ret;
    LPVOID version;
    DWORD versize, handle;
    UINT sz;

    versize = GetFileVersionInfoSizeW( filename, &handle );
    if (!versize)
        return NULL;

    version = msi_alloc( versize );
    if (!version)
        return NULL;

    GetFileVersionInfoW( filename, 0, versize, version );

    if (!VerQueryValueW( version, name, (LPVOID *)&ptr, &sz ))
    {
        msi_free( version );
        return NULL;
    }

    ret = msi_alloc( sz );
    memcpy( ret, ptr, sz );

    msi_free( version );
    return ret;
}