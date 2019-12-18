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
struct TYPE_10__ {TYPE_1__* package; } ;
typedef  TYPE_2__ msi_dialog ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ MSIQUERY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_IterateRecords (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_3__**,char const*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_dialog_add_font ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT msi_dialog_build_font_list( msi_dialog *dialog )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        '`','T','e','x','t','S','t','y','l','e','`',0};
    MSIQUERY *view;
    UINT r;

    TRACE("dialog %p\n", dialog );

    r = MSI_OpenQuery( dialog->package->db, &view, query );
    if( r != ERROR_SUCCESS )
        return r;

    r = MSI_IterateRecords( view, NULL, msi_dialog_add_font, dialog );
    msiobj_release( &view->hdr );
    return r;
}