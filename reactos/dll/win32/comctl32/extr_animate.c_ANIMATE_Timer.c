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
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  cs; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_1__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ANIMATE_DrawFrame (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT ANIMATE_Timer(ANIMATE_INFO *infoPtr)
{
    HDC	hDC;

    if ((hDC = GetDC(infoPtr->hwndSelf)) != 0)
    {
        EnterCriticalSection(&infoPtr->cs);
        ANIMATE_DrawFrame(infoPtr, hDC);
        LeaveCriticalSection(&infoPtr->cs);

	ReleaseDC(infoPtr->hwndSelf, hDC);
    }

    return 0;
}