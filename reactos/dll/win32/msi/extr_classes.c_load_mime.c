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
struct TYPE_9__ {int /*<<< orphan*/  entry; void* clsid; int /*<<< orphan*/  Class; int /*<<< orphan*/  suffix; int /*<<< orphan*/  Extension; void* ContentType; } ;
struct TYPE_8__ {int /*<<< orphan*/  mimes; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  TYPE_2__ MSIMIME ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_given_class (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  load_given_extension (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 void* msi_dup_record_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MSIMIME *load_mime( MSIPACKAGE* package, MSIRECORD *row )
{
    LPCWSTR extension;
    MSIMIME *mt;

    /* fill in the data */

    mt = msi_alloc_zero( sizeof(MSIMIME) );
    if (!mt)
        return mt;

    mt->ContentType = msi_dup_record_field( row, 1 ); 
    TRACE("loading mime %s\n", debugstr_w(mt->ContentType));

    extension = MSI_RecordGetString( row, 2 );
    mt->Extension = load_given_extension( package, extension );
    mt->suffix = strdupW( extension );

    mt->clsid = msi_dup_record_field( row, 3 );
    mt->Class = load_given_class( package, mt->clsid );

    list_add_tail( &package->mimes, &mt->entry );

    return mt;
}