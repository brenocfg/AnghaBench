#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/ * path; TYPE_1__* File; } ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
struct TYPE_6__ {int /*<<< orphan*/ * TargetPath; } ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  TYPE_3__ MSIFILEPATCH ;

/* Variables and functions */
 scalar_t__ ApplyPatchToFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_INSTALL_FAILURE ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  MoveFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_create_temp_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT patch_file( MSIPACKAGE *package, MSIFILEPATCH *patch )
{
    UINT r = ERROR_SUCCESS;
    WCHAR *tmpfile = msi_create_temp_file( package->db );

    if (!tmpfile) return ERROR_INSTALL_FAILURE;
    if (ApplyPatchToFileW( patch->path, patch->File->TargetPath, tmpfile, 0 ))
    {
        DeleteFileW( patch->File->TargetPath );
        MoveFileW( tmpfile, patch->File->TargetPath );
    }
    else
    {
        WARN("failed to patch %s: %08x\n", debugstr_w(patch->File->TargetPath), GetLastError());
        r = ERROR_INSTALL_FAILURE;
    }
    DeleteFileW( patch->path );
    DeleteFileW( tmpfile );
    msi_free( tmpfile );
    return r;
}