#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dialog_control {char const* member_1; TYPE_2__* member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_1__* package; } ;
typedef  TYPE_2__ msi_dialog ;
typedef  char WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ MSIQUERY ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_IterateRecords (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dialog_control*) ; 
 int /*<<< orphan*/  MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_3__**,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  map_event ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dialog_map_events( msi_dialog *dialog, const WCHAR *control )
{
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
         '`','E','v','e','n','t','M','a','p','p','i','n','g','`',' ',
         'W','H','E','R','E',' ','`','D','i','a','l','o','g','_','`',' ','=',' ','\'','%','s','\'',' ',
         'A','N','D',' ','`','C','o','n','t','r','o','l','_','`',' ','=',' ','\'','%','s','\'',0};
    MSIQUERY *view;
    struct dialog_control dialog_control =
    {
        dialog,
        control
    };

    if (!MSI_OpenQuery( dialog->package->db, &view, queryW, dialog->name, control ))
    {
        MSI_IterateRecords( view, NULL, map_event, &dialog_control );
        msiobj_release( &view->hdr );
    }
}