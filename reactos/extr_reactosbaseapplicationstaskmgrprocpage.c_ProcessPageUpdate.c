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

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ListView_GetSelectedCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hProcessPageEndProcessButton ; 
 int /*<<< orphan*/  hProcessPageListCtrl ; 

void ProcessPageUpdate(void)
{
    /* Enable or disable the "End Process" button */
    if (ListView_GetSelectedCount(hProcessPageListCtrl))
        EnableWindow(hProcessPageEndProcessButton, TRUE);
    else
        EnableWindow(hProcessPageEndProcessButton, FALSE);
}