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
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CX_ICON ; 
 int /*<<< orphan*/  CY_ICON ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDI_BIN ; 
 int /*<<< orphan*/  IDI_STRING ; 
 int /*<<< orphan*/  ILC_MASK ; 
 void* ImageList_AddIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ImageList_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ImageList_GetImageCount (int /*<<< orphan*/ *) ; 
 void* Image_Bin ; 
 void* Image_String ; 
 scalar_t__ LISTVIEW_NUM_ICONS ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int /*<<< orphan*/  ListView_SetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadIconW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hInst ; 

__attribute__((used)) static BOOL InitListViewImageLists(HWND hwndLV)
{
    HIMAGELIST himl;  /* handle to image list  */
    HICON hico;       /* handle to icon  */

    /* Create the image list.  */
    if ((himl = ImageList_Create(CX_ICON, CY_ICON,
                                 ILC_MASK, 0, LISTVIEW_NUM_ICONS)) == NULL)
    {
        return FALSE;
    }

    hico = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_BIN));
    Image_Bin = ImageList_AddIcon(himl, hico);

    hico = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_STRING));
    Image_String = ImageList_AddIcon(himl, hico);

    /* Fail if not all of the images were added.  */
    if (ImageList_GetImageCount(himl) < LISTVIEW_NUM_ICONS)
    {
        return FALSE;
    }

    /* Associate the image list with the tree view control.  */
    (void)ListView_SetImageList(hwndLV, himl, LVSIL_SMALL);

    return TRUE;
}