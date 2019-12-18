#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* fieldspec; struct TYPE_4__* fieldRect; struct TYPE_4__* buflen; int /*<<< orphan*/  hwndSelf; scalar_t__ hMonthCal; scalar_t__ hUpdown; scalar_t__ hwndCheckbut; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
DATETIME_Destroy (DATETIME_INFO *infoPtr)
{
    if (infoPtr->hwndCheckbut)
	DestroyWindow(infoPtr->hwndCheckbut);
    if (infoPtr->hUpdown)
	DestroyWindow(infoPtr->hUpdown);
    if (infoPtr->hMonthCal) 
        DestroyWindow(infoPtr->hMonthCal);
    SetWindowLongPtrW( infoPtr->hwndSelf, 0, 0 ); /* clear infoPtr */
    Free (infoPtr->buflen);
    Free (infoPtr->fieldRect);
    Free (infoPtr->fieldspec);
    Free (infoPtr);
    return 0;
}