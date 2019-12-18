#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int wState; scalar_t__ hWndLBox; int /*<<< orphan*/  textRect; int /*<<< orphan*/  buttonRect; int /*<<< orphan*/  self; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CBF_DROPPED ; 
 int CBF_NOREDRAW ; 
 int /*<<< orphan*/  CBN_CLOSEUP ; 
 int /*<<< orphan*/  CBN_SELENDCANCEL ; 
 int /*<<< orphan*/  CBN_SELENDOK ; 
 scalar_t__ CBS_DROPDOWN ; 
 scalar_t__ CBS_SIMPLE ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  CB_NOTIFY (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCapture () ; 
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 int RDW_ERASE ; 
 int RDW_INVALIDATE ; 
 int RDW_NOCHILDREN ; 
 int RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UnionRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CBRollUp( LPHEADCOMBO lphc, BOOL ok, BOOL bButton )
{
   HWND	hWnd = lphc->self;

   TRACE("[%p]: sel ok? [%i] dropped? [%i]\n",
	 lphc->self, ok, (INT)(lphc->wState & CBF_DROPPED));

   CB_NOTIFY( lphc, (ok) ? CBN_SELENDOK : CBN_SELENDCANCEL );

   if( IsWindow( hWnd ) && CB_GETTYPE(lphc) != CBS_SIMPLE )
   {

       if( lphc->wState & CBF_DROPPED )
       {
	   RECT	rect;

	   lphc->wState &= ~CBF_DROPPED;
	   ShowWindow( lphc->hWndLBox, SW_HIDE );

           if(GetCapture() == lphc->hWndLBox)
           {
               ReleaseCapture();
           }

	   if( CB_GETTYPE(lphc) == CBS_DROPDOWN )
	   {
	       rect = lphc->buttonRect;
	   }
	   else
           {
	       if( bButton )
	       {
		 UnionRect( &rect,
			    &lphc->buttonRect,
			    &lphc->textRect);
	       }
	       else
		 rect = lphc->textRect;

	       bButton = TRUE;
	   }

	   if( bButton && !(lphc->wState & CBF_NOREDRAW) )
	       RedrawWindow( hWnd, &rect, 0, RDW_INVALIDATE |
			       RDW_ERASE | RDW_UPDATENOW | RDW_NOCHILDREN );
	   CB_NOTIFY( lphc, CBN_CLOSEUP );
       }
   }
}