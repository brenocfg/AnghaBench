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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HDROP ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DragFinish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DragQueryFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadClipboardDataFromFile (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 

__attribute__((used)) static void LoadClipboardFromDrop(HDROP hDrop)
{
    WCHAR szFileName[MAX_PATH];

    DragQueryFileW(hDrop, 0, szFileName, ARRAYSIZE(szFileName));
    DragFinish(hDrop);

    LoadClipboardDataFromFile(szFileName);
}