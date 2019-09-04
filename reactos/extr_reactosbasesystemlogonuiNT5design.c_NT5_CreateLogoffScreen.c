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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  NT5_DrawLogoffCaptionText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT5_DrawLogoffIcon (int /*<<< orphan*/ ) ; 

VOID
NT5_CreateLogoffScreen(LPWSTR lpText,
                       HDC hdcMem)
{
    /* Draw the reactos logo */
    NT5_DrawLogoffIcon(hdcMem);

    /* Draw the first text string */
    NT5_DrawLogoffCaptionText(lpText, hdcMem);
}