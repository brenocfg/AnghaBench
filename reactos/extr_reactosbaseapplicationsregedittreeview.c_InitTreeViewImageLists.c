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
typedef  scalar_t__ HICON ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDI_CLOSED_FILE ; 
 int /*<<< orphan*/  IDI_OPEN_FILE ; 
 int /*<<< orphan*/  IDI_ROOT ; 
 int ILC_COLOR32 ; 
 int ILC_MASK ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 void* ImageList_AddIcon (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ImageList_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ ImageList_GetImageCount (int /*<<< orphan*/ *) ; 
 void* Image_Closed ; 
 void* Image_Open ; 
 void* Image_Root ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 scalar_t__ NUM_ICONS ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TVSIL_NORMAL ; 
 int /*<<< orphan*/  TreeView_SetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 

__attribute__((used)) static BOOL InitTreeViewImageLists(HWND hwndTV)
{
    HIMAGELIST himl;  /* handle to image list  */
    HICON hico;       /* handle to icon  */

    /* Create the image list.  */
    if ((himl = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
                                 GetSystemMetrics(SM_CYSMICON),
                                 ILC_MASK | ILC_COLOR32,
                                 0,
                                 NUM_ICONS)) == NULL)
    {
        return FALSE;
    }

    /* Add the open file, closed file, and document bitmaps.  */
    hico = LoadImageW(hInst,
                      MAKEINTRESOURCEW(IDI_OPEN_FILE),
                      IMAGE_ICON,
                      GetSystemMetrics(SM_CXSMICON),
                      GetSystemMetrics(SM_CYSMICON),
                      0);
    if (hico)
    {
        Image_Open = ImageList_AddIcon(himl, hico);
        DestroyIcon(hico);
    }

    hico = LoadImageW(hInst,
                      MAKEINTRESOURCEW(IDI_CLOSED_FILE),
                      IMAGE_ICON,
                      GetSystemMetrics(SM_CXSMICON),
                      GetSystemMetrics(SM_CYSMICON),
                      0);
    if (hico)
    {
        Image_Closed = ImageList_AddIcon(himl, hico);
        DestroyIcon(hico);
    }

    hico = LoadImageW(hInst,
                      MAKEINTRESOURCEW(IDI_ROOT),
                      IMAGE_ICON,
                      GetSystemMetrics(SM_CXSMICON),
                      GetSystemMetrics(SM_CYSMICON),
                      0);
    if (hico)
    {
        Image_Root = ImageList_AddIcon(himl, hico);
        DestroyIcon(hico);
    }

    /* Fail if not all of the images were added.  */
    if (ImageList_GetImageCount(himl) < NUM_ICONS)
    {
        ImageList_Destroy(himl);
        return FALSE;
    }

    /* Associate the image list with the tree view control.  */
    (void)TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL);

    return TRUE;
}