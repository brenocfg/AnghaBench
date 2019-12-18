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
struct TYPE_8__ {TYPE_1__* package; } ;
typedef  TYPE_2__ msi_dialog ;
typedef  char WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ MSIRECORD ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 TYPE_3__* MSI_QueryGetRecord (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_3__*,int) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPWSTR msi_dialog_get_uitext( msi_dialog *dialog, LPCWSTR key )
{
    MSIRECORD *rec;
    LPWSTR text;

    static const WCHAR query[] = {
        's','e','l','e','c','t',' ','*',' ',
        'f','r','o','m',' ','`','U','I','T','e','x','t','`',' ',
        'w','h','e','r','e',' ','`','K','e','y','`',' ','=',' ','\'','%','s','\'',0
    };

    rec = MSI_QueryGetRecord( dialog->package->db, query, key );
    if (!rec) return NULL;
    text = strdupW( MSI_RecordGetString( rec, 2 ) );
    msiobj_release( &rec->hdr );
    return text;
}