#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int wState; int /*<<< orphan*/  textRect; int /*<<< orphan*/  self; int /*<<< orphan*/  hWndLBox; } ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int CBF_EDIT ; 
 int CBF_FOCUSED ; 
 int /*<<< orphan*/  CBN_KILLFOCUS ; 
 int /*<<< orphan*/  CBRollUp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CBS_DROPDOWNLIST ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  CB_NOTIFY (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_CARETOFF ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void COMBO_KillFocus( LPHEADCOMBO lphc )
{
   HWND	hWnd = lphc->self;

   if( lphc->wState & CBF_FOCUSED )
   {
       CBRollUp( lphc, FALSE, TRUE );
       if( IsWindow( hWnd ) )
       {
           if( CB_GETTYPE(lphc) == CBS_DROPDOWNLIST )
               SendMessageW(lphc->hWndLBox, LB_CARETOFF, 0, 0);

	   lphc->wState &= ~CBF_FOCUSED;

           /* redraw text */
	   if( !(lphc->wState & CBF_EDIT) )
	     InvalidateRect(lphc->self, &lphc->textRect, TRUE);

           CB_NOTIFY( lphc, CBN_KILLFOCUS );
       }
   }
}