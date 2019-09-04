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
struct TYPE_8__ {int /*<<< orphan*/  FilterID; int /*<<< orphan*/  DisplayID; } ;
struct TYPE_7__ {int lStructSize; char* lpstrDefExt; int /*<<< orphan*/  Flags; void* nMaxFileTitle; int /*<<< orphan*/  lpstrFileTitle; void* nMaxFile; int /*<<< orphan*/  lpstrFile; int /*<<< orphan*/ * lpstrFilter; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_1__ OPENFILENAME ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ FILTERPAIR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BuildFilterStrings (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COUNT_OF (TYPE_2__*) ; 
 int /*<<< orphan*/  FileNameBuffer ; 
 int /*<<< orphan*/  FileTitleBuffer ; 
 int /*<<< orphan*/  IDS_FLT_ALLFILES ; 
 int /*<<< orphan*/  IDS_FLT_ALLFILES_FLT ; 
 int /*<<< orphan*/  IDS_FLT_HIVFILES ; 
 int /*<<< orphan*/  IDS_FLT_HIVFILES_FLT ; 
 int /*<<< orphan*/  IDS_FLT_REGEDIT4 ; 
 int /*<<< orphan*/  IDS_FLT_REGEDIT4_FLT ; 
 int /*<<< orphan*/  IDS_FLT_REGFILES ; 
 int /*<<< orphan*/  IDS_FLT_REGFILES_FLT ; 
 int /*<<< orphan*/  OFN_HIDEREADONLY ; 
 int /*<<< orphan*/  TRUE ; 
 void* _MAX_PATH ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL InitOpenFileName(HWND hWnd, OPENFILENAME* pofn)
{
    FILTERPAIR FilterPairs[4];
    static WCHAR Filter[1024];

    memset(pofn, 0, sizeof(OPENFILENAME));
    pofn->lStructSize = sizeof(OPENFILENAME);
    pofn->hwndOwner = hWnd;
    pofn->hInstance = hInst;

    /* create filter string */
    FilterPairs[0].DisplayID = IDS_FLT_REGFILES;
    FilterPairs[0].FilterID = IDS_FLT_REGFILES_FLT;
    FilterPairs[1].DisplayID = IDS_FLT_HIVFILES;
    FilterPairs[1].FilterID = IDS_FLT_HIVFILES_FLT;
    FilterPairs[2].DisplayID = IDS_FLT_REGEDIT4;
    FilterPairs[2].FilterID = IDS_FLT_REGEDIT4_FLT;
    FilterPairs[3].DisplayID = IDS_FLT_ALLFILES;
    FilterPairs[3].FilterID = IDS_FLT_ALLFILES_FLT;
    BuildFilterStrings(Filter, FilterPairs, COUNT_OF(FilterPairs));

    pofn->lpstrFilter = Filter;
    pofn->lpstrFile = FileNameBuffer;
    pofn->nMaxFile = _MAX_PATH;
    pofn->lpstrFileTitle = FileTitleBuffer;
    pofn->nMaxFileTitle = _MAX_PATH;
    pofn->Flags = OFN_HIDEREADONLY;
    pofn->lpstrDefExt = L"reg";
    return TRUE;
}