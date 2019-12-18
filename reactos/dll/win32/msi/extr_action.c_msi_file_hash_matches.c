#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  TargetPath; } ;
struct TYPE_6__ {int dwFileHashInfoSize; } ;
typedef  TYPE_1__ MSIFILEHASHINFO ;
typedef  TYPE_2__ MSIFILE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ msi_get_filehash (int /*<<< orphan*/ ,TYPE_1__*) ; 

BOOL msi_file_hash_matches( MSIFILE *file )
{
    UINT r;
    MSIFILEHASHINFO hash;

    hash.dwFileHashInfoSize = sizeof(MSIFILEHASHINFO);
    r = msi_get_filehash( file->TargetPath, &hash );
    if (r != ERROR_SUCCESS)
        return FALSE;

    return !memcmp( &hash, &file->hash, sizeof(MSIFILEHASHINFO) );
}