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
struct TYPE_3__ {int nrFields; int /*<<< orphan*/ * fieldRect; int /*<<< orphan*/  checkbox; int /*<<< orphan*/  calbutton; } ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int INT ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int DTHT_CHECKBOX ; 
 int DTHT_MCPOPUP ; 
 int DTHT_NONE ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_point (int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT
DATETIME_HitTest (const DATETIME_INFO *infoPtr, POINT pt)
{
    int i;

    TRACE ("%s\n", wine_dbgstr_point(&pt));

    if (PtInRect (&infoPtr->calbutton, pt)) return DTHT_MCPOPUP;
    if (PtInRect (&infoPtr->checkbox, pt)) return DTHT_CHECKBOX;

    for (i = 0; i < infoPtr->nrFields; i++) {
        if (PtInRect (&infoPtr->fieldRect[i], pt)) return i;
    }

    return DTHT_NONE;
}