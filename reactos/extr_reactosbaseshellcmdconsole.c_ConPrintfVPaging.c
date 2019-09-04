#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  PCON_PAGER ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConWritePaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int OUTPUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  PagePrompt ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _vstprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ *) ; 

BOOL ConPrintfVPaging(PCON_PAGER Pager, BOOL StartPaging, LPTSTR szFormat, va_list arg_ptr)
{
    // INT len;
    TCHAR szOut[OUTPUT_BUFFER_SIZE];

    /* Return if no string has been given */
    if (szFormat == NULL)
        return TRUE;

    /*len =*/ _vstprintf(szOut, szFormat, arg_ptr);

    // return ConPutsPaging(Pager, PagePrompt, StartPaging, szOut);
    return ConWritePaging(Pager, PagePrompt, StartPaging,
                          szOut, wcslen(szOut));
}