#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {size_t NumSettings; TYPE_2__* pSettings; } ;
struct TYPE_5__ {int /*<<< orphan*/  s; int /*<<< orphan*/  i; } ;
struct TYPE_6__ {int Type; TYPE_1__ Value; int /*<<< orphan*/  Key; } ;
typedef  int SIZE_T ;
typedef  TYPE_3__* PRDPSETTINGS ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAXKEY ; 
 int MAXVALUE ; 
 size_t NUM_SETTINGS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lpSettings ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
WriteRdpFile(HANDLE hFile,
             PRDPSETTINGS pRdpSettings)
{
    WCHAR line[MAXKEY + MAXVALUE + 4];
    SIZE_T BytesToWrite;
    ULONG BytesWritten;
    BOOL bRet;
    INT i, k;

    for (i = 0; i < pRdpSettings->NumSettings; i++)
    {
        /* only write out values in the lpSettings struct */
        for (k = 0; k < NUM_SETTINGS; k++)
        {
            if (wcscmp(lpSettings[k], pRdpSettings->pSettings[i].Key) == 0)
            {
                if (pRdpSettings->pSettings[i].Type == L'i')
                {
                    _snwprintf(line, MAXKEY + MAXVALUE + 4, L"%s:i:%d\r\n",
                               pRdpSettings->pSettings[i].Key,
                               pRdpSettings->pSettings[i].Value.i);
                }
                else
                {
                    _snwprintf(line, MAXKEY + MAXVALUE + 4, L"%s:s:%s\r\n",
                               pRdpSettings->pSettings[i].Key,
                               pRdpSettings->pSettings[i].Value.s);
                }

                BytesToWrite = wcslen(line) * sizeof(WCHAR);

                bRet = WriteFile(hFile,
                                 line,
                                 BytesToWrite,
                                 &BytesWritten,
                                 NULL);
                if (!bRet || BytesWritten == 0)
                    return FALSE;
            }
        }
    }

    return TRUE;
}