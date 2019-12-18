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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {char* path; } ;
typedef  TYPE_1__ MSIDATABASE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int GetFullPathNameW (char const*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  URLIS_URL ; 
 scalar_t__ UrlIsW (char const*,int /*<<< orphan*/ ) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 int /*<<< orphan*/  msi_set_property (TYPE_1__*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  szOriginalDatabase ; 

UINT msi_set_original_database_property( MSIDATABASE *db, const WCHAR *package )
{
    UINT r;

    if (UrlIsW( package, URLIS_URL ))
        r = msi_set_property( db, szOriginalDatabase, package, -1 );
    else if (package[0] == '#')
        r = msi_set_property( db, szOriginalDatabase, db->path, -1 );
    else
    {
        DWORD len;
        WCHAR *path;

        if (!(len = GetFullPathNameW( package, 0, NULL, NULL ))) return GetLastError();
        if (!(path = msi_alloc( len * sizeof(WCHAR) ))) return ERROR_OUTOFMEMORY;
        len = GetFullPathNameW( package, len, path, NULL );
        r = msi_set_property( db, szOriginalDatabase, path, len );
        msi_free( path );
    }
    return r;
}