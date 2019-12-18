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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {scalar_t__ pPrinterName; } ;
typedef  TYPE_1__* LPPRINTER_INFO_2A ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 size_t CB_ERR ; 
 int /*<<< orphan*/  CB_FINDSTRINGEXACT ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  EnumPrintersA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,size_t*,size_t*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetDefaultPrinterA (char*,size_t*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PRINTER_ENUM_LOCAL ; 
 size_t SendDlgItemMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT PRINTDLG_SetUpPrinterListComboA(HWND hDlg, UINT id, LPCSTR name)
{
    DWORD needed, num;
    INT i;
    LPPRINTER_INFO_2A pi;
    EnumPrintersA(PRINTER_ENUM_LOCAL, NULL, 2, NULL, 0, &needed, &num);
    pi = HeapAlloc(GetProcessHeap(), 0, needed);
    EnumPrintersA(PRINTER_ENUM_LOCAL, NULL, 2, (LPBYTE)pi, needed, &needed,
		  &num);

    SendDlgItemMessageA(hDlg, id, CB_RESETCONTENT, 0, 0);
    
    for(i = 0; i < num; i++) {
        SendDlgItemMessageA(hDlg, id, CB_ADDSTRING, 0,
			    (LPARAM)pi[i].pPrinterName );
    }
    HeapFree(GetProcessHeap(), 0, pi);
    if(!name ||
       (i = SendDlgItemMessageA(hDlg, id, CB_FINDSTRINGEXACT, -1,
				(LPARAM)name)) == CB_ERR) {

        char buf[260];
        DWORD dwBufLen = ARRAY_SIZE(buf);
        if (name != NULL)
            WARN("Can't find %s in printer list so trying to find default\n",
	        debugstr_a(name));
	if(!GetDefaultPrinterA(buf, &dwBufLen))
	    return num;
	i = SendDlgItemMessageA(hDlg, id, CB_FINDSTRINGEXACT, -1, (LPARAM)buf);
	if(i == CB_ERR)
	    FIXME("Can't find default printer in printer list\n");
    }
    SendDlgItemMessageA(hDlg, id, CB_SETCURSEL, i, 0);
    return num;
}