#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  top; scalar_t__ bottom; } ;
struct TYPE_12__ {TYPE_7__ droppedRect; int /*<<< orphan*/  textRect; int /*<<< orphan*/  buttonRect; int /*<<< orphan*/  self; } ;
struct TYPE_11__ {int bottom; int top; int right; int left; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__* LPHEADCOMBO ;

/* Variables and functions */
 int /*<<< orphan*/  CBCalcPlacement (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int CBGetTextAreaHeight (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CBResetPos (TYPE_2__*,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CBS_SIMPLE ; 
 scalar_t__ CB_GETTYPE (TYPE_2__*) ; 
 int COMBO_YBORDERSIZE () ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOREDRAW ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  TRACE (char*,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void COMBO_Size( LPHEADCOMBO lphc )
{
  /*
   * Those controls are always the same height. So we have to make sure
   * they are not resized to another value.
   */
  if( CB_GETTYPE(lphc) != CBS_SIMPLE )
  {
    int newComboHeight, curComboHeight, curComboWidth;
    RECT rc;

    GetWindowRect(lphc->self, &rc);
    curComboHeight = rc.bottom - rc.top;
    curComboWidth = rc.right - rc.left;
    newComboHeight = CBGetTextAreaHeight(lphc->self, lphc) + 2*COMBO_YBORDERSIZE();

    /*
     * Resizing a combobox has another side effect, it resizes the dropped
     * rectangle as well. However, it does it only if the new height for the
     * combobox is more than the height it should have. In other words,
     * if the application resizing the combobox only had the intention to resize
     * the actual control, for example, to do the layout of a dialog that is
     * resized, the height of the dropdown is not changed.
     */
    if( curComboHeight > newComboHeight )
    {
      TRACE("oldComboHeight=%d, newComboHeight=%d, oldDropBottom=%d, oldDropTop=%d\n",
            curComboHeight, newComboHeight, lphc->droppedRect.bottom,
            lphc->droppedRect.top);
      lphc->droppedRect.bottom = lphc->droppedRect.top + curComboHeight - newComboHeight;
    }
    /*
     * Restore original height
     */
    if( curComboHeight != newComboHeight )
      SetWindowPos(lphc->self, 0, 0, 0, curComboWidth, newComboHeight,
            SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOREDRAW);
  }

  CBCalcPlacement(lphc->self,
		  lphc,
		  &lphc->textRect,
		  &lphc->buttonRect,
		  &lphc->droppedRect);

  CBResetPos( lphc, &lphc->textRect, &lphc->droppedRect, TRUE );
}