#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msi_dialog ;
struct TYPE_4__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ msi_control ;
typedef  int /*<<< orphan*/  hrefW ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int mask; char* szUrl; scalar_t__ iLink; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ LITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int LIF_ITEMINDEX ; 
 int LIF_URL ; 
 int /*<<< orphan*/  LM_GETITEM ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShellExecuteW (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isspaceW (char const) ; 
 int /*<<< orphan*/  memicmpW (char const*,char const*,int) ; 
 int strlenW (char const*) ; 
 char toupperW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT msi_dialog_hyperlink_handler( msi_dialog *dialog, msi_control *control, WPARAM param )
{
    static const WCHAR hrefW[] = {'h','r','e','f'};
    static const WCHAR openW[] = {'o','p','e','n',0};
    int len, len_href = sizeof(hrefW) / sizeof(hrefW[0]);
    const WCHAR *p, *q;
    WCHAR quote = 0;
    LITEM item;

    item.mask     = LIF_ITEMINDEX | LIF_URL;
    item.iLink    = 0;
    item.szUrl[0] = 0;

    SendMessageW( control->hwnd, LM_GETITEM, 0, (LPARAM)&item );

    p = item.szUrl;
    while (*p && *p != '<') p++;
    if (!*p++) return ERROR_SUCCESS;
    if (toupperW( *p++ ) != 'A' || !isspaceW( *p++ )) return ERROR_SUCCESS;
    while (*p && isspaceW( *p )) p++;

    len = strlenW( p );
    if (len > len_href && !memicmpW( p, hrefW, len_href ))
    {
        p += len_href;
        while (*p && isspaceW( *p )) p++;
        if (!*p || *p++ != '=') return ERROR_SUCCESS;
        while (*p && isspaceW( *p )) p++;

        if (*p == '\"' || *p == '\'') quote = *p++;
        q = p;
        if (quote)
        {
            while (*q && *q != quote) q++;
            if (*q != quote) return ERROR_SUCCESS;
        }
        else
        {
            while (*q && *q != '>' && !isspaceW( *q )) q++;
            if (!*q) return ERROR_SUCCESS;
        }
        item.szUrl[q - item.szUrl] = 0;
        ShellExecuteW( NULL, openW, p, NULL, NULL, SW_SHOWNORMAL );
    }
    return ERROR_SUCCESS;
}