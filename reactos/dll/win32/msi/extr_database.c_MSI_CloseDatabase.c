#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {scalar_t__ tempfolder; scalar_t__ deletefile; int /*<<< orphan*/  storage; scalar_t__ strings; scalar_t__ path; } ;
typedef  int /*<<< orphan*/  MSIOBJECTHDR ;
typedef  TYPE_1__ MSIDATABASE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileW (scalar_t__) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cached_tables (TYPE_1__*) ; 
 int /*<<< orphan*/  free_streams (TYPE_1__*) ; 
 int /*<<< orphan*/  free_transforms (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_destroy_stringtable (scalar_t__) ; 
 int /*<<< orphan*/  msi_free (scalar_t__) ; 

__attribute__((used)) static VOID MSI_CloseDatabase( MSIOBJECTHDR *arg )
{
    MSIDATABASE *db = (MSIDATABASE *) arg;

    msi_free(db->path);
    free_streams( db );
    free_cached_tables( db );
    free_transforms( db );
    if (db->strings) msi_destroy_stringtable( db->strings );
    IStorage_Release( db->storage );
    if (db->deletefile)
    {
        DeleteFileW( db->deletefile );
        msi_free( db->deletefile );
    }
    msi_free( db->tempfolder );
}