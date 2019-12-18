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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {TYPE_1__* Pagefile; int /*<<< orphan*/  hListBox; void* bModified; int /*<<< orphan*/  hSelf; } ;
struct TYPE_7__ {int OldMinSize; int OldMaxSize; int NewMinSize; int NewMaxSize; void* bUsed; } ;
typedef  TYPE_2__* PVIRTMEM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PAGEFILELIST ; 
 int /*<<< orphan*/  InitPagefileList (TYPE_2__*) ; 
 int /*<<< orphan*/  ParseMemSettings (TYPE_2__*) ; 
 int /*<<< orphan*/  ReadPageFileSettings (TYPE_2__*) ; 
 int /*<<< orphan*/  SetListBoxColumns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
OnInitVirtMemDialog(HWND hwnd, PVIRTMEM pVirtMem)
{
    INT i;

    pVirtMem->hSelf = hwnd;
    pVirtMem->hListBox = GetDlgItem(hwnd, IDC_PAGEFILELIST);
    pVirtMem->bModified = FALSE;

    SetListBoxColumns(pVirtMem->hListBox);

    for (i = 0; i < 26; i++)
    {
        pVirtMem->Pagefile[i].bUsed = FALSE;
        pVirtMem->Pagefile[i].OldMinSize = -1;
        pVirtMem->Pagefile[i].OldMaxSize = -1;
        pVirtMem->Pagefile[i].NewMinSize = -1;
        pVirtMem->Pagefile[i].NewMaxSize = -1;
    }

    /* Load the pagefile systems from the reg */
    ReadPageFileSettings(pVirtMem);

    /* Parse our settings and set up dialog */
    ParseMemSettings(pVirtMem);

    InitPagefileList(pVirtMem);
}