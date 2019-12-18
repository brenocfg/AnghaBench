#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_2__* package; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  char WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;

/* Variables and functions */
 int /*<<< orphan*/ * MSI_QueryGetRecord (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MSIRECORD *msi_get_dialog_record( msi_dialog *dialog )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ',
        'F','R','O','M',' ','D','i','a','l','o','g',' ',
        'W','H','E','R','E',' ',
           '`','D','i','a','l','o','g','`',' ','=',' ','\'','%','s','\'',0};
    MSIPACKAGE *package = dialog->package;
    MSIRECORD *rec = NULL;

    TRACE("%p %s\n", dialog, debugstr_w(dialog->name) );

    rec = MSI_QueryGetRecord( package->db, query, dialog->name );
    if( !rec )
        WARN("query failed for dialog %s\n", debugstr_w(dialog->name));

    return rec;
}