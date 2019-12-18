#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  MulDiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG HeightFromPointSize(DWORD dwPointSize)
{
    LONG lHeight;
    HDC hDC;

    hDC = GetDC(NULL);
    lHeight = -MulDiv(dwPointSize, GetDeviceCaps(hDC, LOGPIXELSY), 720);
    ReleaseDC(NULL, hDC);

    return lHeight;
}