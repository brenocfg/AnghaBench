#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 scalar_t__ IDS_ERROR_BASE ; 
 int LoadStringW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* MSI_QueryGetRecord (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/ * msi_dup_record_field (TYPE_1__*,int) ; 
 int /*<<< orphan*/  msi_hInstance ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

LPWSTR msi_get_error_message(MSIDATABASE *db, int error)
{
    static const WCHAR query[] =
        {'S','E','L','E','C','T',' ','`','M','e','s','s','a','g','e','`',' ',
         'F','R','O','M',' ','`','E','r','r','o','r','`',' ','W','H','E','R','E',' ',
         '`','E','r','r','o','r','`',' ','=',' ','%','i',0};
    MSIRECORD *record;
    LPWSTR ret = NULL;

    if ((record = MSI_QueryGetRecord(db, query, error)))
    {
        ret = msi_dup_record_field(record, 1);
        msiobj_release(&record->hdr);
    }
    else if (error < 2000)
    {
        int len = LoadStringW(msi_hInstance, IDS_ERROR_BASE + error, (LPWSTR) &ret, 0);
        if (len)
        {
            ret = msi_alloc((len + 1) * sizeof(WCHAR));
            LoadStringW(msi_hInstance, IDS_ERROR_BASE + error, ret, len + 1);
        }
        else
            ret = NULL;
    }

    return ret;
}