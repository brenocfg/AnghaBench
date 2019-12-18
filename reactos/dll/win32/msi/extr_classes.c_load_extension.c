#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  action; int /*<<< orphan*/  Feature; int /*<<< orphan*/  Mime; void* ProgIDText; int /*<<< orphan*/  ProgID; int /*<<< orphan*/  Component; void* Extension; int /*<<< orphan*/  entry; int /*<<< orphan*/  verbs; } ;
struct TYPE_10__ {int /*<<< orphan*/  extensions; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIEXTENSION ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  INSTALLSTATE_UNKNOWN ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_given_mime (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_given_progid (TYPE_1__*,void*) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_get_loaded_component (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_get_loaded_feature (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MSIEXTENSION *load_extension( MSIPACKAGE* package, MSIRECORD *row )
{
    MSIEXTENSION *ext;
    LPCWSTR buffer;

    /* fill in the data */

    ext = msi_alloc_zero( sizeof(MSIEXTENSION) );
    if (!ext)
        return NULL;

    list_init( &ext->verbs );

    list_add_tail( &package->extensions, &ext->entry );

    ext->Extension = msi_dup_record_field( row, 1 );
    TRACE("loading extension %s\n", debugstr_w(ext->Extension));

    buffer = MSI_RecordGetString( row, 2 );
    ext->Component = msi_get_loaded_component( package, buffer );

    ext->ProgIDText = msi_dup_record_field( row, 3 );
    ext->ProgID = load_given_progid( package, ext->ProgIDText );

    buffer = MSI_RecordGetString( row, 4 );
    ext->Mime = load_given_mime( package, buffer );

    buffer = MSI_RecordGetString(row,5);
    ext->Feature = msi_get_loaded_feature( package, buffer );
    ext->action = INSTALLSTATE_UNKNOWN;
    return ext;
}