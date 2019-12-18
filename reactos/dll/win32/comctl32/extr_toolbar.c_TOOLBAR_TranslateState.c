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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int fsState; scalar_t__ bHot; } ;
typedef  TYPE_1__ TBUTTON_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CDIS_CHECKED ; 
 int /*<<< orphan*/  CDIS_DISABLED ; 
 int /*<<< orphan*/  CDIS_HOT ; 
 int /*<<< orphan*/  CDIS_INDETERMINATE ; 
 int /*<<< orphan*/  CDIS_MARKED ; 
 int /*<<< orphan*/  CDIS_SELECTED ; 
 int TBSTATE_CHECKED ; 
 int TBSTATE_ENABLED ; 
 int TBSTATE_INDETERMINATE ; 
 int TBSTATE_MARKED ; 
 int TBSTATE_PRESSED ; 

__attribute__((used)) static UINT
TOOLBAR_TranslateState(const TBUTTON_INFO *btnPtr)
{
    UINT retstate = 0;

    retstate |= (btnPtr->fsState & TBSTATE_CHECKED) ? CDIS_CHECKED  : 0;
    retstate |= (btnPtr->fsState & TBSTATE_PRESSED) ? CDIS_SELECTED : 0;
    retstate |= (btnPtr->fsState & TBSTATE_ENABLED) ? 0 : CDIS_DISABLED;
    retstate |= (btnPtr->fsState & TBSTATE_MARKED ) ? CDIS_MARKED   : 0;
    retstate |= (btnPtr->bHot                     ) ? CDIS_HOT      : 0;
    retstate |= ((btnPtr->fsState & (TBSTATE_ENABLED|TBSTATE_INDETERMINATE)) == (TBSTATE_ENABLED|TBSTATE_INDETERMINATE)) ? CDIS_INDETERMINATE : 0;
    /* NOTE: we don't set CDIS_GRAYED, CDIS_FOCUS, CDIS_DEFAULT */
    return retstate;
}