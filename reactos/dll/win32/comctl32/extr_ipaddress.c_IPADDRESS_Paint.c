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
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ IPADDRESS_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPADDRESS_Draw (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static LRESULT IPADDRESS_Paint (const IPADDRESS_INFO *infoPtr, HDC hdc)
{
    PAINTSTRUCT ps;

    TRACE("\n");

    if (hdc) return IPADDRESS_Draw (infoPtr, hdc);

    hdc = BeginPaint (infoPtr->Self, &ps);
    IPADDRESS_Draw (infoPtr, hdc);
    EndPaint (infoPtr->Self, &ps);
    return 0;
}