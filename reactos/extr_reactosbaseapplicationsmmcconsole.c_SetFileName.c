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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/ * pFileName; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_1__* PCONSOLE_CHILDFRM_WND ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _tcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
SetFileName(
    PCONSOLE_CHILDFRM_WND Info,
    PWSTR pFileName)
{
    DPRINT1("SetFileName(&p \'%S\')\n", Info, pFileName);

    if (Info->pFileName != NULL)
    {
        HeapFree(GetProcessHeap(), 0, Info->pFileName);
        Info->pFileName = NULL;
    }

    if (pFileName != NULL)
    {
        Info->pFileName = HeapAlloc(GetProcessHeap(),
                                    0,
                                    (_tcslen(pFileName) + 1) * sizeof(TCHAR));
        if (Info->pFileName != NULL)
            _tcscpy(Info->pFileName, pFileName);
    }
}