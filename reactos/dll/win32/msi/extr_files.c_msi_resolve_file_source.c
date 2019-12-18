#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/ * File; int /*<<< orphan*/  LongName; int /*<<< orphan*/  ShortName; TYPE_1__* Component; scalar_t__ IsCompressed; } ;
struct TYPE_4__ {int /*<<< orphan*/  Directory; } ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_2__ MSIFILE ;

/* Variables and functions */
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_build_directory_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_resolve_source_folder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

WCHAR *msi_resolve_file_source( MSIPACKAGE *package, MSIFILE *file )
{
    WCHAR *p, *path;

    TRACE("Working to resolve source of file %s\n", debugstr_w(file->File));

    if (file->IsCompressed) return NULL;

    p = msi_resolve_source_folder( package, file->Component->Directory, NULL );
    path = msi_build_directory_name( 2, p, file->ShortName );

    if (file->LongName && GetFileAttributesW( path ) == INVALID_FILE_ATTRIBUTES)
    {
        msi_free( path );
        path = msi_build_directory_name( 2, p, file->LongName );
    }
    msi_free( p );
    TRACE("file %s source resolves to %s\n", debugstr_w(file->File), debugstr_w(path));
    return path;
}