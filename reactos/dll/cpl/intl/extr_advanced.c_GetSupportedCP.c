#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  CodePageName; } ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; struct TYPE_7__* NextItem; int /*<<< orphan*/ * Name; scalar_t__ CodePage; } ;
typedef  int /*<<< orphan*/  PINT ;
typedef  TYPE_1__* PCPAGE ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  TYPE_2__ CPINFOEX ;
typedef  int /*<<< orphan*/  CPAGE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CODEPAGE_NOT_REMOVEABLE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetACP () ; 
 scalar_t__ GetCPInfoExW (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ GetOEMCP () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int MAX_PATH ; 
 TYPE_1__* PCPage ; 
 int /*<<< orphan*/  SetupFindFirstLine (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupGetIntField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNICODE_NULL ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static BOOL
GetSupportedCP(
    HINF hInf)
{
    WCHAR szSection[MAX_PATH];
    INFCONTEXT Context, Context2;
    PCPAGE pCodePage;
    CPINFOEX cpInfEx;
    UINT uiCodePage;

    if (!SetupFindFirstLine(hInf,
                            L"CodePages",
                            NULL,
                            &Context))
        return FALSE;

    for (;;)
    {
        if (SetupGetIntField(&Context, 0, (PINT)&uiCodePage))
        {
            pCodePage = HeapAlloc(GetProcessHeap(), 0, sizeof(CPAGE));
            if (pCodePage == NULL)
                return FALSE;

            pCodePage->CodePage = uiCodePage;
            pCodePage->Flags = 0;
            (pCodePage->Name)[0] = UNICODE_NULL;

            if (GetCPInfoExW(uiCodePage, 0, &cpInfEx))
            {
                wcscpy(pCodePage->Name, cpInfEx.CodePageName);
            }
            else
            {
                SetupGetStringFieldW(&Context, 1, pCodePage->Name, MAX_PATH, NULL);
            }

            if (wcslen(pCodePage->Name) != 0)
            {
                pCodePage->NextItem = PCPage;
                PCPage = pCodePage;

                wsprintf(szSection, L"CODEPAGE_REMOVE_%d", uiCodePage);

                if ((uiCodePage == GetACP()) ||
                    (uiCodePage == GetOEMCP()) ||
                    (!SetupFindFirstLineW(hInf, szSection, L"AddReg", &Context2)))
                {
                    pCodePage->Flags |= CODEPAGE_NOT_REMOVEABLE;
                }
            }
            else
            {
                HeapFree(GetProcessHeap(), 0, pCodePage);
            }
        }

        if (!SetupFindNextLine(&Context, &Context))
            break;
    }

    return TRUE;
}