#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msi_file_state ;
struct TYPE_22__ {int /*<<< orphan*/  dwFileVersionLS; int /*<<< orphan*/  dwFileVersionMS; } ;
typedef  TYPE_3__ WCHAR ;
typedef  TYPE_3__ VS_FIXEDFILEINFO ;
struct TYPE_24__ {scalar_t__ Action; TYPE_1__* assembly; int /*<<< orphan*/  Enabled; } ;
struct TYPE_21__ {scalar_t__ dwFileHashInfoSize; } ;
struct TYPE_23__ {TYPE_3__* File; TYPE_2__ hash; int /*<<< orphan*/  FileSize; int /*<<< orphan*/  TargetPath; TYPE_3__* Version; TYPE_6__* Component; } ;
struct TYPE_20__ {scalar_t__ installed; } ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_5__ MSIFILE ;
typedef  TYPE_6__ MSICOMPONENT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ INSTALLSTATE_LOCAL ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (TYPE_3__*) ; 
 scalar_t__ is_obsoleted_by_patch (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ msi_compare_file_versions (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ msi_compare_font_versions (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ msi_file_hash_matches (TYPE_5__*) ; 
 TYPE_3__* msi_font_version_from_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (TYPE_3__*) ; 
 scalar_t__ msi_get_component_action (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  msi_get_disk_file_size (int /*<<< orphan*/ ) ; 
 TYPE_3__* msi_get_disk_file_version (int /*<<< orphan*/ ) ; 
 scalar_t__ msi_is_global_assembly (TYPE_6__*) ; 
 int /*<<< orphan*/  msifs_hashmatch ; 
 int /*<<< orphan*/  msifs_missing ; 
 int /*<<< orphan*/  msifs_overwrite ; 
 int /*<<< orphan*/  msifs_present ; 
 int /*<<< orphan*/  msifs_skipped ; 

__attribute__((used)) static msi_file_state calculate_install_state( MSIPACKAGE *package, MSIFILE *file )
{
    MSICOMPONENT *comp = file->Component;
    VS_FIXEDFILEINFO *file_version;
    WCHAR *font_version;
    msi_file_state state;
    DWORD size;

    comp->Action = msi_get_component_action( package, comp );
    if (!comp->Enabled || comp->Action != INSTALLSTATE_LOCAL || (comp->assembly && comp->assembly->installed))
    {
        TRACE("skipping %s (not scheduled for install)\n", debugstr_w(file->File));
        return msifs_skipped;
    }
    if (is_obsoleted_by_patch( package, file ))
    {
        TRACE("skipping %s (obsoleted by patch)\n", debugstr_w(file->File));
        return msifs_skipped;
    }
    if ((msi_is_global_assembly( comp ) && !comp->assembly->installed) ||
        GetFileAttributesW( file->TargetPath ) == INVALID_FILE_ATTRIBUTES)
    {
        TRACE("installing %s (missing)\n", debugstr_w(file->File));
        return msifs_missing;
    }
    if (file->Version)
    {
        if ((file_version = msi_get_disk_file_version( file->TargetPath )))
        {
            if (msi_compare_file_versions( file_version, file->Version ) < 0)
            {
                TRACE("overwriting %s (new version %s old version %u.%u.%u.%u)\n",
                      debugstr_w(file->File), debugstr_w(file->Version),
                      HIWORD(file_version->dwFileVersionMS), LOWORD(file_version->dwFileVersionMS),
                      HIWORD(file_version->dwFileVersionLS), LOWORD(file_version->dwFileVersionLS));
                state = msifs_overwrite;
            }
            else
            {
                TRACE("keeping %s (new version %s old version %u.%u.%u.%u)\n",
                      debugstr_w(file->File), debugstr_w(file->Version),
                      HIWORD(file_version->dwFileVersionMS), LOWORD(file_version->dwFileVersionMS),
                      HIWORD(file_version->dwFileVersionLS), LOWORD(file_version->dwFileVersionLS));
                state = msifs_present;
            }
            msi_free( file_version );
            return state;
        }
        else if ((font_version = msi_font_version_from_file( file->TargetPath )))
        {
            if (msi_compare_font_versions( font_version, file->Version ) < 0)
            {
                TRACE("overwriting %s (new version %s old version %s)\n",
                      debugstr_w(file->File), debugstr_w(file->Version), debugstr_w(font_version));
                state = msifs_overwrite;
            }
            else
            {
                TRACE("keeping %s (new version %s old version %s)\n",
                      debugstr_w(file->File), debugstr_w(file->Version), debugstr_w(font_version));
                state = msifs_present;
            }
            msi_free( font_version );
            return state;
        }
    }
    if ((size = msi_get_disk_file_size( file->TargetPath )) != file->FileSize)
    {
        TRACE("overwriting %s (old size %u new size %u)\n", debugstr_w(file->File), size, file->FileSize);
        return msifs_overwrite;
    }
    if (file->hash.dwFileHashInfoSize)
    {
        if (msi_file_hash_matches( file ))
        {
            TRACE("keeping %s (hash match)\n", debugstr_w(file->File));
            return msifs_hashmatch;
        }
        else
        {
            TRACE("overwriting %s (hash mismatch)\n", debugstr_w(file->File));
            return msifs_overwrite;
        }
    }
    /* assume present */
    TRACE("keeping %s\n", debugstr_w(file->File));
    return msifs_present;
}