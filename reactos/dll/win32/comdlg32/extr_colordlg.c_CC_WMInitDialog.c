#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WNDPROC ;
struct TYPE_16__ {int bottom; int top; } ;
struct TYPE_19__ {int h; int s; int l; TYPE_3__* lpcc; TYPE_1__ fullsize; int /*<<< orphan*/  msetrgb; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_18__ {int lStructSize; int Flags; scalar_t__ rgbResult; scalar_t__ lpfnHook; } ;
struct TYPE_17__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ CHOOSECOLORW ;
typedef  TYPE_4__ CCPRIV ;

/* Variables and functions */
 int CC_FULLOPEN ; 
 scalar_t__ CC_HookCallChk (TYPE_3__*) ; 
 int CC_PREVENTFULLOPEN ; 
 int /*<<< orphan*/  CC_PaintCross (TYPE_4__*) ; 
 int /*<<< orphan*/  CC_PaintSelectedColor (TYPE_4__*) ; 
 int /*<<< orphan*/  CC_PaintTriangle (TYPE_4__*) ; 
 int CC_RGBINIT ; 
 void* CC_RGBtoHSL (char,scalar_t__) ; 
 int CC_SHOWHELP ; 
 int /*<<< orphan*/  CC_SwitchToFullSize (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int CallWindowProcA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EM_LIMITTEXT ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int GetBValue (scalar_t__) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 int GetGValue (scalar_t__) ; 
 int GetRValue (scalar_t__) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int IDC_COLOR_ADD ; 
 int IDC_COLOR_BL ; 
 int IDC_COLOR_DEFINE ; 
 int IDC_COLOR_EDIT_B ; 
 int IDC_COLOR_EDIT_G ; 
 int IDC_COLOR_EDIT_H ; 
 int IDC_COLOR_EDIT_L ; 
 int IDC_COLOR_EDIT_R ; 
 int IDC_COLOR_EDIT_S ; 
 int IDC_COLOR_GRAPH ; 
 int IDC_COLOR_HL ; 
 int IDC_COLOR_RES ; 
 int IDC_COLOR_RESULT ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 int /*<<< orphan*/  RegisterWindowMessageA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETRGBSTRINGA ; 
 int /*<<< orphan*/  SM_CXDLGFRAME ; 
 int SWP_NOMOVE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int TRUE ; 
 int /*<<< orphan*/  WM_INITDIALOG ; 
 int /*<<< orphan*/  cpos ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int j ; 
 scalar_t__** predefcolors ; 
 int pshHelp ; 
 int /*<<< orphan*/  szColourDialogProp ; 

__attribute__((used)) static LRESULT CC_WMInitDialog( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
   CHOOSECOLORW *cc = (CHOOSECOLORW*)lParam;
   int i, res;
   int r, g, b;
   HWND hwnd;
   RECT rect;
   POINT point;
   CCPRIV *lpp;

   TRACE("WM_INITDIALOG lParam=%08lX\n", lParam);

   if (cc->lStructSize != sizeof(CHOOSECOLORW))
   {
       EndDialog(hDlg, 0);
       return FALSE;
   }

   lpp = heap_alloc_zero(sizeof(*lpp));
   lpp->lpcc = cc;
   lpp->hwndSelf = hDlg;

   SetPropW( hDlg, szColourDialogProp, lpp );

   if (!(lpp->lpcc->Flags & CC_SHOWHELP))
      ShowWindow(GetDlgItem(hDlg, pshHelp), SW_HIDE);
   lpp->msetrgb = RegisterWindowMessageA(SETRGBSTRINGA);

#if 0
   cpos = MAKELONG(5,7); /* init */
   if (lpp->lpcc->Flags & CC_RGBINIT)
   {
     for (i = 0; i < 6; i++)
       for (j = 0; j < 8; j++)
        if (predefcolors[i][j] == lpp->lpcc->rgbResult)
        {
          cpos = MAKELONG(i,j);
          goto found;
        }
   }
   found:
   /* FIXME: Draw_a_focus_rect & set_init_values */
#endif

   GetWindowRect(hDlg, &lpp->fullsize);
   if (lpp->lpcc->Flags & CC_FULLOPEN || lpp->lpcc->Flags & CC_PREVENTFULLOPEN)
   {
      hwnd = GetDlgItem(hDlg, IDC_COLOR_DEFINE);
      EnableWindow(hwnd, FALSE);
   }
   if (!(lpp->lpcc->Flags & CC_FULLOPEN ) || lpp->lpcc->Flags & CC_PREVENTFULLOPEN)
   {
      rect = lpp->fullsize;
      res = rect.bottom - rect.top;
      hwnd = GetDlgItem(hDlg, IDC_COLOR_GRAPH); /* cut at left border */
      point.x = point.y = 0;
      ClientToScreen(hwnd, &point);
      ScreenToClient(hDlg,&point);
      GetClientRect(hDlg, &rect);
      point.x += GetSystemMetrics(SM_CXDLGFRAME);
      SetWindowPos(hDlg, 0, 0, 0, point.x, res, SWP_NOMOVE|SWP_NOZORDER);

      for (i = IDC_COLOR_EDIT_H; i <= IDC_COLOR_EDIT_B; i++)
         ShowWindow( GetDlgItem(hDlg, i), SW_HIDE);
      for (i = IDC_COLOR_HL; i <= IDC_COLOR_BL; i++)
         ShowWindow( GetDlgItem(hDlg, i), SW_HIDE);
      ShowWindow( GetDlgItem(hDlg, IDC_COLOR_RES), SW_HIDE);
      ShowWindow( GetDlgItem(hDlg, IDC_COLOR_ADD), SW_HIDE);
      ShowWindow( GetDlgItem(hDlg, IDC_COLOR_GRAPH), SW_HIDE);
      ShowWindow( GetDlgItem(hDlg, IDC_COLOR_RESULT), SW_HIDE);
      ShowWindow( GetDlgItem(hDlg, 1090 ), SW_HIDE);
   }
   else
      CC_SwitchToFullSize(lpp, NULL);
   res = TRUE;
   for (i = IDC_COLOR_EDIT_H; i <= IDC_COLOR_EDIT_B; i++)
     SendMessageA( GetDlgItem(hDlg, i), EM_LIMITTEXT, 3, 0);  /* max 3 digits:  xyz  */
   if (CC_HookCallChk(lpp->lpcc))
   {
          res = CallWindowProcA( (WNDPROC)lpp->lpcc->lpfnHook, hDlg, WM_INITDIALOG, wParam, lParam);
   }

   /* Set the initial values of the color chooser dialog */
   r = GetRValue(lpp->lpcc->rgbResult);
   g = GetGValue(lpp->lpcc->rgbResult);
   b = GetBValue(lpp->lpcc->rgbResult);

   CC_PaintSelectedColor(lpp);
   lpp->h = CC_RGBtoHSL('H', lpp->lpcc->rgbResult);
   lpp->s = CC_RGBtoHSL('S', lpp->lpcc->rgbResult);
   lpp->l = CC_RGBtoHSL('L', lpp->lpcc->rgbResult);

   /* Doing it the long way because CC_EditSetRGB/HSL doesn't seem to work */
   SetDlgItemInt(hDlg, IDC_COLOR_EDIT_H, lpp->h, TRUE);
   SetDlgItemInt(hDlg, IDC_COLOR_EDIT_S, lpp->s, TRUE);
   SetDlgItemInt(hDlg, IDC_COLOR_EDIT_L, lpp->l, TRUE);
   SetDlgItemInt(hDlg, IDC_COLOR_EDIT_R, r, TRUE);
   SetDlgItemInt(hDlg, IDC_COLOR_EDIT_G, g, TRUE);
   SetDlgItemInt(hDlg, IDC_COLOR_EDIT_B, b, TRUE);

   CC_PaintCross(lpp);
   CC_PaintTriangle(lpp);

   return res;
}