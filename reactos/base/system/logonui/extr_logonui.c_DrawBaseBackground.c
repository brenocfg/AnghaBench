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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  NT5_DrawBaseBackground (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HDC
DrawBaseBackground(HDC hdcDesktop)
{
    HDC hdcMem;

    hdcMem = NT5_DrawBaseBackground(hdcDesktop);

    return hdcMem;
}