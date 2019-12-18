#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  Directory; TYPE_3__* assembly; } ;
struct TYPE_10__ {int /*<<< orphan*/  const* tempdir; } ;
struct TYPE_9__ {void* TargetPath; void* File; int /*<<< orphan*/  FileName; TYPE_6__* Component; } ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIFILE ;
typedef  TYPE_3__ MSIASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* create_temp_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 void* msi_build_directory_name (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (void*) ; 
 int /*<<< orphan*/ * msi_get_target_folder (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_is_global_assembly (TYPE_6__*) ; 

__attribute__((used)) static void set_target_path( MSIPACKAGE *package, MSIFILE *file )
{
    msi_free( file->TargetPath );
    if (msi_is_global_assembly( file->Component ))
    {
        MSIASSEMBLY *assembly = file->Component->assembly;

        if (!assembly->tempdir) assembly->tempdir = create_temp_dir( package->db );
        file->TargetPath = msi_build_directory_name( 2, assembly->tempdir, file->FileName );
    }
    else
    {
        const WCHAR *dir = msi_get_target_folder( package, file->Component->Directory );
        file->TargetPath = msi_build_directory_name( 2, dir, file->FileName );
    }

    TRACE("file %s resolves to %s\n", debugstr_w(file->File), debugstr_w(file->TargetPath));
}