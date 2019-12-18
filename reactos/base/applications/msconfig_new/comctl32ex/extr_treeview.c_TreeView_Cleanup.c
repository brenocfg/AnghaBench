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

/* Variables and functions */
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVSIL_STATE ; 
 int /*<<< orphan*/  TreeView_GetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void TreeView_Cleanup(HWND hTree)
{
    // FIXME: Should we do it always, or only when the custom image list was set?
    ImageList_Destroy(TreeView_GetImageList(hTree, TVSIL_STATE));
}