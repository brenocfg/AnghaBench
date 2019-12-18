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
struct TYPE_4__ {int /*<<< orphan*/  Self; } ;
typedef  TYPE_1__ SYSLINK_INFO ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSLINK_Draw (TYPE_1__ const*,scalar_t__) ; 

__attribute__((used)) static LRESULT SYSLINK_Paint (const SYSLINK_INFO *infoPtr, HDC hdcParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    hdc = hdcParam ? hdcParam : BeginPaint (infoPtr->Self, &ps);
    if (hdc)
    {
        SYSLINK_Draw (infoPtr, hdc);
        if (!hdcParam) EndPaint (infoPtr->Self, &ps);
    }
    return 0;
}