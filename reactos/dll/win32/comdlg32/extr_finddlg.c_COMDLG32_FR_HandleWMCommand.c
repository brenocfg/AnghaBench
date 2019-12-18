#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_10__ {int Flags; int /*<<< orphan*/  hwndOwner; int /*<<< orphan*/ * lpstrReplaceWith; int /*<<< orphan*/ * lpstrFindWhat; int /*<<< orphan*/  wReplaceWithLen; int /*<<< orphan*/  wFindWhatLen; } ;
struct TYPE_9__ {TYPE_2__* fra; TYPE_1__* frw; } ;
struct TYPE_11__ {TYPE_4__ fr; TYPE_3__ user_fr; } ;
struct TYPE_8__ {int Flags; int /*<<< orphan*/  lpstrReplaceWith; int /*<<< orphan*/  lpstrFindWhat; } ;
struct TYPE_7__ {int /*<<< orphan*/  lpstrReplaceWith; int /*<<< orphan*/  lpstrFindWhat; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;
typedef  TYPE_5__ COMDLG32_FR_Data ;
typedef  int BOOL ;

/* Variables and functions */
 int BN_CLICKED ; 
 int COMDLG32_FR_GetFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int EN_CHANGE ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int FR_DIALOGTERM ; 
 int FR_DOWN ; 
 int FR_FINDNEXT ; 
 int FR_MASK ; 
 int FR_REPLACE ; 
 int FR_REPLACEALL ; 
 int FR_WINE_REPLACE ; 
 int FR_WINE_UNICODE ; 
 int /*<<< orphan*/  FindReplaceMessage ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  GetDlgItemTextA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HelpMessage ; 
#define  IDCANCEL 132 
#define  IDOK 131 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SendDlgItemMessageA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 int edt1 ; 
 int edt2 ; 
#define  psh1 130 
#define  psh2 129 
#define  pshHelp 128 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void COMDLG32_FR_HandleWMCommand(HWND hDlgWnd, COMDLG32_FR_Data *pData, int Id, int NotifyCode)
{
	DWORD flag;

	pData->user_fr.fra->Flags &= ~FR_MASK;	/* Clear return flags */
	if(pData->fr.Flags & FR_WINE_REPLACE)	/* Replace always goes down... */
		pData->user_fr.fra->Flags |= FR_DOWN;

	if(NotifyCode == BN_CLICKED)
        {
		switch(Id)
		{
		case IDOK: /* Find Next */
			if(GetDlgItemTextA(hDlgWnd, edt1, pData->fr.lpstrFindWhat, pData->fr.wFindWhatLen) > 0)
                        {
				pData->user_fr.fra->Flags |= COMDLG32_FR_GetFlags(hDlgWnd) | FR_FINDNEXT;
                                if(pData->fr.Flags & FR_WINE_UNICODE)
                                {
                                    MultiByteToWideChar( CP_ACP, 0, pData->fr.lpstrFindWhat, -1,
                                                         pData->user_fr.frw->lpstrFindWhat,
                                                         0x7fffffff );
                                }
                                else
                                {
					strcpy(pData->user_fr.fra->lpstrFindWhat, pData->fr.lpstrFindWhat);
                                }
				SendMessageA(pData->fr.hwndOwner, FindReplaceMessage, 0, (LPARAM)pData->user_fr.fra);
                        }
			break;

		case IDCANCEL:
			pData->user_fr.fra->Flags |= COMDLG32_FR_GetFlags(hDlgWnd) | FR_DIALOGTERM;
			SendMessageA(pData->fr.hwndOwner, FindReplaceMessage, 0, (LPARAM)pData->user_fr.fra);
		        DestroyWindow(hDlgWnd);
			break;

                case psh2: /* Replace All */
			flag = FR_REPLACEALL;
                        goto Replace;

                case psh1: /* Replace */
			flag = FR_REPLACE;
Replace:
			if((pData->fr.Flags & FR_WINE_REPLACE)
                        && GetDlgItemTextA(hDlgWnd, edt1, pData->fr.lpstrFindWhat, pData->fr.wFindWhatLen) > 0)
                        {
				pData->fr.lpstrReplaceWith[0] = 0; /* In case the next GetDlgItemText Fails */
				GetDlgItemTextA(hDlgWnd, edt2, pData->fr.lpstrReplaceWith, pData->fr.wReplaceWithLen);
				pData->user_fr.fra->Flags |= COMDLG32_FR_GetFlags(hDlgWnd) | flag;
                                if(pData->fr.Flags & FR_WINE_UNICODE)
                                {
                                    MultiByteToWideChar( CP_ACP, 0, pData->fr.lpstrFindWhat, -1,
                                                         pData->user_fr.frw->lpstrFindWhat,
                                                         0x7fffffff );
                                    MultiByteToWideChar( CP_ACP, 0, pData->fr.lpstrReplaceWith, -1,
                                                         pData->user_fr.frw->lpstrReplaceWith,
                                                         0x7fffffff );
                                }
                                else
                                {
					strcpy(pData->user_fr.fra->lpstrFindWhat, pData->fr.lpstrFindWhat);
					strcpy(pData->user_fr.fra->lpstrReplaceWith, pData->fr.lpstrReplaceWith);
                                }
				SendMessageA(pData->fr.hwndOwner, FindReplaceMessage, 0, (LPARAM)pData->user_fr.fra);
                        }
			break;

		case pshHelp:
			pData->user_fr.fra->Flags |= COMDLG32_FR_GetFlags(hDlgWnd);
			SendMessageA(pData->fr.hwndOwner, HelpMessage, (WPARAM)hDlgWnd, (LPARAM)pData->user_fr.fra);
			break;
                }
        }
        else if(NotifyCode == EN_CHANGE && Id == edt1)
	{
		BOOL enable = SendDlgItemMessageA(hDlgWnd, edt1, WM_GETTEXTLENGTH, 0, 0) > 0;
		EnableWindow(GetDlgItem(hDlgWnd, IDOK), enable);
                if(pData->fr.Flags & FR_WINE_REPLACE)
                {
			EnableWindow(GetDlgItem(hDlgWnd, psh1), enable);
			EnableWindow(GetDlgItem(hDlgWnd, psh2), enable);
                }
	}
}