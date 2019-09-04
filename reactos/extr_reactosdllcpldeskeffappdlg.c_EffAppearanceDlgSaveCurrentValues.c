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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  GLOBALS ;

/* Variables and functions */

__attribute__((used)) static VOID
EffAppearanceDlgSaveCurrentValues(HWND hwndDlg, GLOBALS *g)
{
    /* The settings get saved at the end of ApplyScheme() in theme.c,
     * when clicking Apply in the main dialog. */
}