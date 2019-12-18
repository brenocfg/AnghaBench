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
typedef  int /*<<< orphan*/  msi_dialog ;
struct TYPE_5__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ msi_control ;
typedef  int /*<<< orphan*/  lvc ;
typedef  char WCHAR ;
struct TYPE_6__ {int mask; char* pszText; int /*<<< orphan*/  cx; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ LVCOLUMNW ;
typedef  int LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int DWORD ;

/* Variables and functions */
 int LVCF_SUBITEM ; 
 int LVCF_TEXT ; 
 int LVCF_WIDTH ; 
 int /*<<< orphan*/  LVM_INSERTCOLUMNW ; 
 int MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  atolW (char*) ; 
 int /*<<< orphan*/ * column_keys ; 
 int /*<<< orphan*/  lstrcpynW (char*,int,int) ; 
 char* msi_alloc (int) ; 
 char* msi_dialog_get_uitext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 int /*<<< orphan*/  str_is_number (char*) ; 
 int strchrW (int,char) ; 
 int /*<<< orphan*/  strcmpW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmpW (char*,char const*,int) ; 
 int /*<<< orphan*/  szZero ; 

__attribute__((used)) static void msi_dialog_vcl_add_columns( msi_dialog *dialog, msi_control *control, MSIRECORD *rec )
{
    LPCWSTR text = MSI_RecordGetString( rec, 10 );
    LPCWSTR begin = text, end;
    WCHAR *num;
    LVCOLUMNW lvc;
    DWORD count = 0;

    static const WCHAR negative[] = {'-',0};

    if (!text) return;

    while ((begin = strchrW( begin, '{' )) && count < 5)
    {
        if (!(end = strchrW( begin, '}' )))
            return;

        num = msi_alloc( (end-begin+1)*sizeof(WCHAR) );
        if (!num)
            return;

        lstrcpynW( num, begin + 1, end - begin );
        begin += end - begin + 1;

        /* empty braces or '0' hides the column */ 
        if ( !num[0] || !strcmpW( num, szZero ) )
        {
            count++;
            msi_free( num );
            continue;
        }

        /* the width must be a positive number
         * if a width is invalid, all remaining columns are hidden
         */
        if ( !strncmpW( num, negative, 1 ) || !str_is_number( num ) ) {
            msi_free( num );
            return;
        }

        ZeroMemory( &lvc, sizeof(lvc) );
        lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
        lvc.cx = atolW( num );
        lvc.pszText = msi_dialog_get_uitext( dialog, column_keys[count] );

        SendMessageW( control->hwnd,  LVM_INSERTCOLUMNW, count++, (LPARAM)&lvc );
        msi_free( lvc.pszText );
        msi_free( num );
    }
}