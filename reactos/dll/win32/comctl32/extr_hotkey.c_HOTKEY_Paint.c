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
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  TYPE_1__ HOTKEY_INFO ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HOTKEY_Refresh (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
HOTKEY_Paint(HOTKEY_INFO *infoPtr, HDC hdc)
{
    if (hdc)
	HOTKEY_Refresh(infoPtr, hdc);
    else {
	PAINTSTRUCT ps;
	hdc = BeginPaint (infoPtr->hwndSelf, &ps);
	HOTKEY_Refresh (infoPtr, hdc);
	EndPaint (infoPtr->hwndSelf, &ps);
    }
}