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
struct TYPE_5__ {int wState; int /*<<< orphan*/  textRect; int /*<<< orphan*/  self; int /*<<< orphan*/  hWndLBox; } ;
typedef  TYPE_1__* LPHEADCOMBO ;

/* Variables and functions */
 int CBF_EDIT ; 
 int CBF_FOCUSED ; 
 int /*<<< orphan*/  CBN_SETFOCUS ; 
 scalar_t__ CBS_DROPDOWNLIST ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  CB_NOTIFY (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_CARETON ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void COMBO_SetFocus( LPHEADCOMBO lphc )
{
   if( !(lphc->wState & CBF_FOCUSED) )
   {
       if( CB_GETTYPE(lphc) == CBS_DROPDOWNLIST )
           SendMessageW(lphc->hWndLBox, LB_CARETON, 0, 0);

       /* This is wrong. Message sequences seem to indicate that this
          is set *after* the notify. */
       /* lphc->wState |= CBF_FOCUSED;  */

       if( !(lphc->wState & CBF_EDIT) )
	 InvalidateRect(lphc->self, &lphc->textRect, TRUE);

       CB_NOTIFY( lphc, CBN_SETFOCUS );
       lphc->wState |= CBF_FOCUSED;
   }
}