#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  patch_file ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_18__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  storage; } ;
struct TYPE_17__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  ProductCode; } ;
struct TYPE_16__ {int /*<<< orphan*/  localfile; int /*<<< orphan*/  registered; } ;
struct TYPE_15__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSISUMMARYINFO ;
typedef  TYPE_2__ MSIPATCHINFO ;
typedef  TYPE_3__ MSIPACKAGE ;
typedef  TYPE_4__ MSIDATABASE ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  INSTALLPROPERTY_LOCALPACKAGEW ; 
 int MAX_PATH ; 
 scalar_t__ MSIDBOPEN_PATCHFILE ; 
 scalar_t__ MSIDBOPEN_READONLY ; 
 scalar_t__ MSI_OpenDatabaseW (int /*<<< orphan*/ *,scalar_t__,TYPE_4__**) ; 
 scalar_t__ MsiGetPatchInfoExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ msi_apply_patch_db (TYPE_3__*,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_free_patchinfo (TYPE_2__*) ; 
 scalar_t__ msi_get_suminfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ msi_parse_patch_summary (TYPE_1__*,TYPE_2__**) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ *) ; 

UINT msi_apply_registered_patch( MSIPACKAGE *package, LPCWSTR patch_code )
{
    UINT r;
    DWORD len;
    WCHAR patch_file[MAX_PATH];
    MSIDATABASE *patch_db;
    MSIPATCHINFO *patch_info;
    MSISUMMARYINFO *si;

    TRACE("%p, %s\n", package, debugstr_w(patch_code));

    len = sizeof(patch_file) / sizeof(WCHAR);
    r = MsiGetPatchInfoExW( patch_code, package->ProductCode, NULL, package->Context,
                            INSTALLPROPERTY_LOCALPACKAGEW, patch_file, &len );
    if (r != ERROR_SUCCESS)
    {
        ERR("failed to get patch filename %u\n", r);
        return r;
    }
    r = MSI_OpenDatabaseW( patch_file, MSIDBOPEN_READONLY + MSIDBOPEN_PATCHFILE, &patch_db );
    if (r != ERROR_SUCCESS)
    {
        ERR("failed to open patch database %s\n", debugstr_w( patch_file ));
        return r;
    }
    r = msi_get_suminfo( patch_db->storage, 0, &si );
    if (r != ERROR_SUCCESS)
    {
        msiobj_release( &patch_db->hdr );
        return r;
    }
    r = msi_parse_patch_summary( si, &patch_info );
    msiobj_release( &si->hdr );
    if (r != ERROR_SUCCESS)
    {
        ERR("failed to parse patch summary %u\n", r);
        msiobj_release( &patch_db->hdr );
        return r;
    }
    patch_info->registered = TRUE;
    patch_info->localfile = strdupW( patch_file );
    if (!patch_info->localfile)
    {
        msiobj_release( &patch_db->hdr );
        msi_free_patchinfo( patch_info );
        return ERROR_OUTOFMEMORY;
    }
    r = msi_apply_patch_db( package, patch_db, patch_info );
    msiobj_release( &patch_db->hdr );
    if (r != ERROR_SUCCESS)
    {
        ERR("failed to apply patch %u\n", r);
        msi_free_patchinfo( patch_info );
    }
    return r;
}