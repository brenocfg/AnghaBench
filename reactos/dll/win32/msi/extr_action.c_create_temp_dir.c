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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  tempfolder; } ;
typedef  TYPE_1__ MSIDATABASE ;

/* Variables and functions */
 scalar_t__ CreateDirectoryW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FILE_ATTRIBUTE_DIRECTORY ; 
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempFileNameW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempPathW (int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ msi_get_property (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ *) ; 
 int strlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szMsi ; 
 int /*<<< orphan*/  szTempFolder ; 

__attribute__((used)) static WCHAR *create_temp_dir( MSIDATABASE *db )
{
    static UINT id;
    WCHAR *ret;

    if (!db->tempfolder)
    {
        WCHAR tmp[MAX_PATH];
        UINT len = sizeof(tmp)/sizeof(tmp[0]);

        if (msi_get_property( db, szTempFolder, tmp, &len ) ||
            GetFileAttributesW( tmp ) != FILE_ATTRIBUTE_DIRECTORY)
        {
            GetTempPathW( MAX_PATH, tmp );
        }
        if (!(db->tempfolder = strdupW( tmp ))) return NULL;
    }

    if ((ret = msi_alloc( (strlenW( db->tempfolder ) + 20) * sizeof(WCHAR) )))
    {
        for (;;)
        {
            if (!GetTempFileNameW( db->tempfolder, szMsi, ++id, ret ))
            {
                msi_free( ret );
                return NULL;
            }
            if (CreateDirectoryW( ret, NULL )) break;
        }
    }

    return ret;
}