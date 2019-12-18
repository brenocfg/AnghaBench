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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/ * msi_dup_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_reset_folders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strrchrW (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  szOriginalDatabase ; 
 int /*<<< orphan*/  szSOURCEDIR ; 
 int /*<<< orphan*/  szSourceDir ; 

UINT msi_set_sourcedir_props(MSIPACKAGE *package, BOOL replace)
{
    WCHAR *source, *check, *p, *db;
    DWORD len;

    if (!(db = msi_dup_property( package->db, szOriginalDatabase )))
        return ERROR_OUTOFMEMORY;

    if (!(p = strrchrW( db, '\\' )) && !(p = strrchrW( db, '/' )))
    {
        msi_free(db);
        return ERROR_SUCCESS;
    }
    len = p - db + 2;
    source = msi_alloc( len * sizeof(WCHAR) );
    lstrcpynW( source, db, len );
    msi_free( db );

    check = msi_dup_property( package->db, szSourceDir );
    if (!check || replace)
    {
        UINT r = msi_set_property( package->db, szSourceDir, source, -1 );
        if (r == ERROR_SUCCESS)
            msi_reset_folders( package, TRUE );
    }
    msi_free( check );

    check = msi_dup_property( package->db, szSOURCEDIR );
    if (!check || replace)
        msi_set_property( package->db, szSOURCEDIR, source, -1 );

    msi_free( check );
    msi_free( source );

    return ERROR_SUCCESS;
}