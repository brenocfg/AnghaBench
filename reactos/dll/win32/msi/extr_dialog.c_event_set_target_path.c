#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* package; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_2__ MSIRECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 TYPE_2__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_SetTargetPathW (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_dup_property (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msi_event_fire (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szSelectionPath ; 

__attribute__((used)) static UINT event_set_target_path( msi_dialog *dialog, const WCHAR *argument )
{
    WCHAR *path = msi_dup_property( dialog->package->db, argument );
    MSIRECORD *rec = MSI_CreateRecord( 1 );
    UINT r = ERROR_SUCCESS;

    MSI_RecordSetStringW( rec, 1, path );
    msi_event_fire( dialog->package, szSelectionPath, rec );
    if (path)
    {
        /* failure to set the path halts the executing of control events */
        r = MSI_SetTargetPathW( dialog->package, argument, path );
        msi_free( path );
    }
    msi_free( &rec->hdr );
    return r;
}