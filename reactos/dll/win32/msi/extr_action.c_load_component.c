#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  assembly; void* ActionRequest; void* Action; void* Installed; void* KeyPath; void* Condition; int /*<<< orphan*/  Attributes; void* Directory; void* ComponentId; void* Component; int /*<<< orphan*/  entry; } ;
struct TYPE_8__ {int /*<<< orphan*/  components; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSICOMPONENT ;
typedef  TYPE_1__* LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 void* INSTALLSTATE_UNKNOWN ; 
 int /*<<< orphan*/  MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_load_assembly (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static UINT load_component( MSIRECORD *row, LPVOID param )
{
    MSIPACKAGE *package = param;
    MSICOMPONENT *comp;

    comp = msi_alloc_zero( sizeof(MSICOMPONENT) );
    if (!comp)
        return ERROR_FUNCTION_FAILED;

    list_add_tail( &package->components, &comp->entry );

    /* fill in the data */
    comp->Component = msi_dup_record_field( row, 1 );

    TRACE("Loading Component %s\n", debugstr_w(comp->Component));

    comp->ComponentId = msi_dup_record_field( row, 2 );
    comp->Directory = msi_dup_record_field( row, 3 );
    comp->Attributes = MSI_RecordGetInteger(row,4);
    comp->Condition = msi_dup_record_field( row, 5 );
    comp->KeyPath = msi_dup_record_field( row, 6 );

    comp->Installed = INSTALLSTATE_UNKNOWN;
    comp->Action = INSTALLSTATE_UNKNOWN;
    comp->ActionRequest = INSTALLSTATE_UNKNOWN;

    comp->assembly = msi_load_assembly( package, comp );
    return ERROR_SUCCESS;
}