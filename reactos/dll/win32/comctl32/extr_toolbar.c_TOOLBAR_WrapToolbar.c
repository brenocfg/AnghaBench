#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fsState; scalar_t__ cx; int fsStyle; scalar_t__ iBitmap; } ;
struct TYPE_7__ {size_t right; size_t left; } ;
struct TYPE_8__ {int dwStyle; int dwExStyle; size_t nIndent; size_t nButtonWidth; int nBitmapWidth; size_t nNumButtons; TYPE_1__ client_rect; TYPE_3__* buttons; } ;
typedef  TYPE_2__ TOOLBAR_INFO ;
typedef  TYPE_3__ TBUTTON_INFO ;
typedef  size_t INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BTNS_DROPDOWN ; 
 int BTNS_SEP ; 
 int CCS_VERT ; 
 scalar_t__ DDARROW_WIDTH ; 
 scalar_t__ FALSE ; 
 size_t SEPARATOR_WIDTH ; 
 int TBSTATE_HIDDEN ; 
 int TBSTATE_WRAP ; 
 int TBSTYLE_EX_VERTICAL ; 
 int TBSTYLE_WRAPABLE ; 
 int /*<<< orphan*/  TRACE (char*,size_t,int,...) ; 
 scalar_t__ TRUE ; 
 scalar_t__ button_has_ddarrow (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void
TOOLBAR_WrapToolbar(TOOLBAR_INFO *infoPtr)
{
    TBUTTON_INFO *btnPtr;
    INT x, cx, i, j, width;
    BOOL bButtonWrap;

    /* 	When the toolbar window style is not TBSTYLE_WRAPABLE,	*/
    /*	no layout is necessary. Applications may use this style */
    /*	to perform their own layout on the toolbar. 		*/
    if( !(infoPtr->dwStyle & TBSTYLE_WRAPABLE) &&
	!(infoPtr->dwExStyle & TBSTYLE_EX_VERTICAL) )  return;

    btnPtr = infoPtr->buttons;
    x  = infoPtr->nIndent;
    width = infoPtr->client_rect.right - infoPtr->client_rect.left;

    bButtonWrap = FALSE;

    TRACE("start ButtonWidth=%d, BitmapWidth=%d, width=%d, nIndent=%d\n",
	  infoPtr->nButtonWidth, infoPtr->nBitmapWidth, width,
	  infoPtr->nIndent);

    for (i = 0; i < infoPtr->nNumButtons; i++ )
    {
	btnPtr[i].fsState &= ~TBSTATE_WRAP;

	if (btnPtr[i].fsState & TBSTATE_HIDDEN)
	    continue;

        if (btnPtr[i].cx > 0)
            cx = btnPtr[i].cx;
        /* horizontal separators are treated as buttons for width    */
	else if ((btnPtr[i].fsStyle & BTNS_SEP) &&
            !(infoPtr->dwStyle & CCS_VERT))
            cx = (btnPtr[i].iBitmap > 0) ? btnPtr[i].iBitmap : SEPARATOR_WIDTH;
	else
	    cx = infoPtr->nButtonWidth;

        if (!btnPtr[i].cx && button_has_ddarrow( infoPtr, btnPtr + i ))
            cx += DDARROW_WIDTH;

	/* Two or more adjacent separators form a separator group.   */
	/* The first separator in a group should be wrapped to the   */
	/* next row if the previous wrapping is on a button.	     */
	if( bButtonWrap &&
		(btnPtr[i].fsStyle & BTNS_SEP) &&
		(i + 1 < infoPtr->nNumButtons ) &&
		(btnPtr[i + 1].fsStyle & BTNS_SEP) )
	{
	    TRACE("wrap point 1 btn %d style %02x\n", i, btnPtr[i].fsStyle);
	    btnPtr[i].fsState |= TBSTATE_WRAP;
	    x = infoPtr->nIndent;
	    i++;
	    bButtonWrap = FALSE;
	    continue;
	}

	/* The layout makes sure the bitmap is visible, but not the button. */
	/* Test added to also wrap after a button that starts a row but     */
	/* is bigger than the area.  - GA  8/01                             */
        if ((x + cx - (infoPtr->nButtonWidth - infoPtr->nBitmapWidth) / 2 > width) ||
            ((x == infoPtr->nIndent) && (cx > width)))
	{
	    BOOL bFound = FALSE;

	    /* 	If the current button is a separator and not hidden,  */
	    /*	go to the next until it reaches a non separator.      */
	    /*	Wrap the last separator if it is before a button.     */
	    while( ( ((btnPtr[i].fsStyle & BTNS_SEP) &&
		      !(btnPtr[i].fsStyle & BTNS_DROPDOWN)) ||
		     (btnPtr[i].fsState & TBSTATE_HIDDEN) ) &&
			i < infoPtr->nNumButtons )
	    {
		i++;
		bFound = TRUE;
	    }

	    if( bFound && i < infoPtr->nNumButtons )
	    {
		i--;
		TRACE("wrap point 2 btn %d style %02x, x=%d, cx=%d\n",
		      i, btnPtr[i].fsStyle, x, cx);
		btnPtr[i].fsState |= TBSTATE_WRAP;
		x = infoPtr->nIndent;
		bButtonWrap = FALSE;
		continue;
	    }
	    else if ( i >= infoPtr->nNumButtons)
		break;

	    /* 	If the current button is not a separator, find the last  */
	    /*	separator and wrap it.   				 */
	    for ( j = i - 1; j >= 0  &&  !(btnPtr[j].fsState & TBSTATE_WRAP); j--)
	    {
		if ((btnPtr[j].fsStyle & BTNS_SEP) &&
			!(btnPtr[j].fsState & TBSTATE_HIDDEN))
		{
		    bFound = TRUE;
		    i = j;
		    TRACE("wrap point 3 btn %d style %02x, x=%d, cx=%d\n",
			  i, btnPtr[i].fsStyle, x, cx);
		    x = infoPtr->nIndent;
		    btnPtr[j].fsState |= TBSTATE_WRAP;
		    bButtonWrap = FALSE;
		    break;
		}
	    }

	    /* 	If no separator available for wrapping, wrap one of 	*/
	    /*  non-hidden previous button.  			     	*/
	    if (!bFound)
	    {
		for ( j = i - 1;
			j >= 0 && !(btnPtr[j].fsState & TBSTATE_WRAP); j--)
		{
		    if (btnPtr[j].fsState & TBSTATE_HIDDEN)
			continue;

		    bFound = TRUE;
		    i = j;
		    TRACE("wrap point 4 btn %d style %02x, x=%d, cx=%d\n",
			  i, btnPtr[i].fsStyle, x, cx);
		    x = infoPtr->nIndent;
		    btnPtr[j].fsState |= TBSTATE_WRAP;
		    bButtonWrap = TRUE;
		    break;
		}
	    }

	    /* If all above failed, wrap the current button. */
	    if (!bFound)
	    {
		TRACE("wrap point 5 btn %d style %02x, x=%d, cx=%d\n",
		      i, btnPtr[i].fsStyle, x, cx);
		btnPtr[i].fsState |= TBSTATE_WRAP;
		x = infoPtr->nIndent;
		if (btnPtr[i].fsStyle & BTNS_SEP )
		    bButtonWrap = FALSE;
		else
		    bButtonWrap = TRUE;
	    }
	}
	else {
	    TRACE("wrap point 6 btn %d style %02x, x=%d, cx=%d\n",
		  i, btnPtr[i].fsStyle, x, cx);
	    x += cx;
	}
    }
}