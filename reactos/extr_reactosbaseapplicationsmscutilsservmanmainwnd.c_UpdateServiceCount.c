#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  hStatus; int /*<<< orphan*/  hListView; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 scalar_t__ AllocAndLoadString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_NUM_SERVICES ; 
 int /*<<< orphan*/  ListView_GetItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_SETTEXT ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInstance ; 

VOID
UpdateServiceCount(PMAIN_WND_INFO Info)
{
    LPWSTR lpNumServices;

    if (AllocAndLoadString(&lpNumServices,
                           hInstance,
                           IDS_NUM_SERVICES))
    {
        WCHAR szNumServices[32];

        INT NumListedServ = ListView_GetItemCount(Info->hListView);

        _snwprintf(szNumServices,
                   31,
                   lpNumServices,
                   NumListedServ);

        SendMessage(Info->hStatus,
                    SB_SETTEXT,
                    0,
                    (LPARAM)szNumServices);

        LocalFree(lpNumServices);
    }
}