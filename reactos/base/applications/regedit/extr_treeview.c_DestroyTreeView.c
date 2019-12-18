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
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ImageList_Destroy (scalar_t__) ; 
 int /*<<< orphan*/  TVSIL_NORMAL ; 
 scalar_t__ TreeView_GetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pathBuffer ; 

void DestroyTreeView(HWND hwndTV)
{
    HIMAGELIST himl;

    if (pathBuffer) HeapFree(GetProcessHeap(), 0, pathBuffer);

    /* Destroy the image list associated with the tree view control */
    himl = TreeView_GetImageList(hwndTV, TVSIL_NORMAL);
    if (himl) ImageList_Destroy(himl);
}